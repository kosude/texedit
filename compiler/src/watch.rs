/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{fmt::Debug, path::Path};

use notify::{
    event::{CreateKind, DataChange, ModifyKind, RemoveKind, RenameMode},
    EventKind, RecommendedWatcher, RecursiveMode, Watcher,
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
) -> CompResult<()> {
    let (tx, rx) = std::sync::mpsc::channel();
    let texpdfc = &texpdfc.as_ref().to_path_buf();

    let compiler = Compiler::new(&texpdfc)
        .document(&input.as_ref().to_path_buf())
        .out_dir(&outdir.as_ref())
        .verbosity(verbosity)
        .to_owned();

    let mut watcher = RecommendedWatcher::new(tx, notify::Config::default())
        .map_err(|e| CompError::WatchStartUpError(e.to_string()))?;
    watcher
        .watch(watch.as_ref(), RecursiveMode::Recursive)
        .map_err(|e| CompError::WatchStartUpError(e.to_string()))?;

    let events = get_tracked_events();

    log::info(format!("Started watch session on path {watch:?}"));

    for res in rx {
        match res {
            Ok(ev) => {
                if ev.paths.contains(&watch.as_ref().to_path_buf()) {
                    return Err(CompError::WatchRuntimeError(
                        format!("Deletion or renaming of watched node {watch:?}").to_string(),
                    ));
                }

                if events.contains(&ev.kind) {
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
            }
            Err(err) => {
                return Err(CompError::WatchRuntimeError(
                    format!("Watch error: {err:?}").to_string(),
                ))
            }
        }
    }

    Ok(())
}
