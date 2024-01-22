/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{fs, process::exit};

use compiler::Compiler;
use error::CompResult;

use crate::error::CompError;

mod compiler;
mod error;
mod files;

fn ret_main() -> CompResult<()> {
    let basep = files::get_exec_loc()?;

    let mut texpdfc = basep.clone();
    texpdfc.push(files::get_texpdfc());

    let mut docpath = basep.clone();
    docpath.push("../../tests/secondone.tex");
    docpath = docpath
        .canonicalize()
        .map_err(|e| CompError::FileNotFoundError(e.to_string()))?;

    let mut outdir = basep.clone();
    outdir.push("tmp");
    fs::create_dir_all(&outdir).map_err(|e| CompError::FilesystemError(e.to_string()))?;

    let res = Compiler::new(&texpdfc)
        .document(&docpath)
        .out_dir(&outdir)
        .compile()
        .map_err(|_| {
            CompError::CompilationError(format!(
                "Failed to compile TeX document at {}",
                docpath.as_os_str().to_str().unwrap()
            ))
        })?;

    println!("{:#?}", res.pdf());

    Ok(())
}

fn main() {
    if let Err(e) = ret_main() {
        e.handle();
    }
    exit(0);
}
