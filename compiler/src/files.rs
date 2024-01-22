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
