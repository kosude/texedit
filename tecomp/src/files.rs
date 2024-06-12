/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{env::current_exe, path::PathBuf};

use crate::error::{CompError, CompResult};

pub fn get_exec_loc() -> CompResult<PathBuf> {
    Ok(current_exe()
        .map_err(|e| CompError::FilesystemError(e.to_string()))?
        .parent()
        .map(PathBuf::from)
        .unwrap())
}

pub fn get_texpdfc() -> &'static str {
    if cfg!(windows) {
        "texpdfc.bat"
    } else {
        "texpdfc.sh"
    }
}

pub fn get_texmf_loc() -> CompResult<PathBuf> {
    Ok(get_exec_loc()?.join("tex").join("texmf"))
}

pub fn str_to_pathbuf<S: AsRef<str>>(str: S, must_exist: bool) -> CompResult<PathBuf> {
    let mut p = PathBuf::from(&str.as_ref());
    if must_exist {
        // canonicalize() checks that the file exists on the fs
        p = p
            .canonicalize()
            .map_err(|e| CompError::FileNotFoundError(format!("{}: {e}", str.as_ref())))?;
    }

    Ok(p)
}
