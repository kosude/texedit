/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

extern crate colored;

use std::process::exit;

use clap::Parser;
use cli::CommandVariant;
use compiler::Compiler;
use error::CompResult;
use files::str_to_pathbuf;

use crate::error::CompError;

mod cli;
mod compiler;
mod error;
mod files;
mod log;
mod watch;

fn main() {
    if let Err(e) = || -> CompResult<()> {
        let args = cli::Cli::parse();

        // get texpdfc script, relative to binary
        let basep = files::get_exec_loc()?;
        let mut texpdfc = basep.clone();
        texpdfc.push(files::get_texpdfc());

        match args.subcommand {
            CommandVariant::Make(o) => {
                Compiler::new(&texpdfc)
                    .document(&str_to_pathbuf(&o.com.input, true)?)
                    .out_dir(&str_to_pathbuf(&o.com.outdir, true)?)
                    .verbosity(if o.com.verbose {
                        compiler::OutputVerbosity::Verbose
                    } else {
                        compiler::OutputVerbosity::NoDelegation
                    })
                    .compile()
                    .map_err(|_| CompError::CompilationError("Compile error".to_string()))?;

                return Ok(());
            }
            CommandVariant::Watch(o) => {
                watch::watch_sync(
                    &texpdfc,
                    &str_to_pathbuf(&o.com.input, true)?,
                    &str_to_pathbuf(&o.com.outdir, true)?,
                    &str_to_pathbuf(&o.watch, true)?,
                )?;

                return Ok(());
            }
        }
    }() {
        e.handle();
    }

    exit(0);
}
