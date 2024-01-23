/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{fs, path::PathBuf, process::exit};

use clap::Parser;
use cli::CommandVariant;
use compiler::{CompileOutput, Compiler};
use error::CompResult;

use crate::error::CompError;

mod cli;
mod compiler;
mod error;
mod files;

fn main() {
    if let Err(e) = || -> CompResult<()> {
        let args = cli::Cli::parse();

        // get texpdfc script, relative to binary
        let basep = files::get_exec_loc()?;
        let mut texpdfc = basep.clone();
        texpdfc.push(files::get_texpdfc());

        match args.subcommand {
            CommandVariant::Make(o) => {
                let input = PathBuf::from(o.input)
                    .canonicalize()
                    .map_err(|e| CompError::FileNotFoundError(e.to_string()))?;

                compile_file(&texpdfc, &input, &o.outdir)?;

                return Ok(());
            }
            CommandVariant::Watch(o) => {
                let input = PathBuf::from(o.input)
                    .canonicalize()
                    .map_err(|e| CompError::FileNotFoundError(e.to_string()))?;

                let watch = PathBuf::from(o.watch)
                    .canonicalize()
                    .map_err(|e| CompError::FileNotFoundError(e.to_string()))?;

                if watch.is_dir() {
                    println!("Watching FILE: {:?}, will compile {:?}", watch, input);
                } else {
                    println!("Watching DIRECTORY: {:?}, will compile {:?}", watch, input);
                }

                // TODO: replace this line with some function that starts a watch procedure that continues indefinitely.
                compile_file(&texpdfc, &input, &o.outdir)?;

                return Ok(());
            }
        }
    }() {
        e.handle();
    }

    exit(0);
}

fn compile_file(texpdfc: &PathBuf, input: &PathBuf, outdir: &str) -> CompResult<CompileOutput> {
    // attempt to create output directory if not exist
    let outdir = PathBuf::from(outdir);
    fs::create_dir_all(&outdir).map_err(|e| CompError::FilesystemError(e.to_string()))?;

    Compiler::new(&texpdfc)
        .document(&input)
        .out_dir(&outdir)
        .compile()
        .map_err(|_| CompError::CompilationError("Compile error".to_string()))
}
