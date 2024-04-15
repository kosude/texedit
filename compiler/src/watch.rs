/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{fmt::Debug, path::Path, time::Duration};

use notify_debouncer_full::{
    new_debouncer,
    notify::{
        event::{CreateKind, DataChange, ModifyKind, RemoveKind, RenameMode},
        EventKind, RecursiveMode, Watcher,
    },
    DebounceEventResult,
};

use crate::{
    compiler::{self, CompileOutput, Compiler},
    error::{CompError, CompResult},
    log,
};

fn get_tracked_events() -> Vec<EventKind> {
    vec![
        EventKind::Create(CreateKind::File),
        EventKind::Modify(ModifyKind::Data(DataChange::Any)),
        EventKind::Modify(ModifyKind::Data(DataChange::Content)),
        EventKind::Modify(ModifyKind::Name(RenameMode::From)),
        EventKind::Remove(RemoveKind::File),
    ]
}

pub fn watch_sync<P: AsRef<Path> + Debug>(
    texpdfc: P,
    input: P,
    outdir: P,
    watch: P,
    verbosity: compiler::OutputVerbosity,
    initial_make: bool,
) -> CompResult<()> {
    let (tx, rx) = std::sync::mpsc::channel();
    let texpdfc = &texpdfc.as_ref().to_path_buf();

    let compiler = Compiler::new(&texpdfc)
        .document(&input.as_ref().to_path_buf())
        .out_dir(&outdir.as_ref())
        .verbosity(verbosity)
        .to_owned();

    // first compilation done here, if it is specified
    if initial_make {
        log::info("Initial pre-watch compilation (-i) specified...");
        watch_compile(&compiler);
    }

    // set up debouncer watcher
    let mut debouncer = new_debouncer(
        Duration::from_millis(500), // this value seems to debounce successfully without too long of a delay
        None,
        move |res: DebounceEventResult| {
            if let Err(e) = tx.send(res) {
                CompError::WatchRuntimeError(format!("When sending event result: {e:?}"))
                    .handle_safe();
            }
        },
    )
    .map_err(|e| CompError::WatchStartUpError(e.to_string()))?;
    debouncer
        .watcher()
        .watch(watch.as_ref(), RecursiveMode::Recursive)
        .map_err(|e| CompError::WatchStartUpError(e.to_string()))?;
    debouncer
        .cache()
        .add_root(watch.as_ref(), RecursiveMode::Recursive);

    log::info(format!("Started watch session on path {watch:?}"));

    let tracked_evs = get_tracked_events();
    for res in rx {
        match res {
            Ok(evs) => {
                // stop with an error if the root file or folder that is being watched is renamed or moved, as otherwise the watcher will hang
                if evs.iter().any(|ev| {
                    (ev.kind == EventKind::Modify(ModifyKind::Name(RenameMode::From))
                        || ev.kind == EventKind::Modify(ModifyKind::Name(RenameMode::Both))
                        || ev.kind == EventKind::Modify(ModifyKind::Name(RenameMode::Any)))
                        && ev.paths.contains(&watch.as_ref().to_path_buf())
                }) {
                    return Err(CompError::WatchRuntimeError(
                        format!("Deletion or renaming of watched node {watch:?}").to_string(),
                    ));
                }

                // check if any of the recieved errors are to be tracked
                if evs.iter().any(|ev| tracked_evs.contains(&ev.kind)) {
                    watch_compile(&compiler);
                }
            }
            Err(errs) => {
                return Err(CompError::WatchRuntimeError(
                    format!("Recieved the following watch errors: {errs:?}").to_string(),
                ))
            }
        }
    }

    Ok(())
}

fn watch_compile(compiler: &Compiler) {
    // handle the error here (safely) instead of in main -- we don't want to exit the program on error when watching.
    if let Err(e) = || -> CompResult<CompileOutput> {
        compiler
            .compile()
            .map_err(|_| CompError::CompilationError("Compile error".to_string()))
    }() {
        // this just prints the error without stopping the process
        e.handle_safe();
    }
}
