/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{fs, path::PathBuf};

use crate::{
    error::{CompError, CompResult},
    files,
};

pub fn get_installed() -> CompResult<Vec<String>> {
    let dir = get_package_dir()?;

    // read folders inside the packages folder (dir)
    let pkgs = fs::read_dir(dir)
        .map_err(|e| CompError::FileNotFoundError(e.to_string()))?
        .map(|res| res.map(|e| e.path()))
        .collect::<Result<Vec<_>, std::io::Error>>()
        .map_err(|e| CompError::FilesystemError(e.to_string()))?;

    // convert pkgs list to contain the folder names
    let mut pkgs = pkgs
        .into_iter()
        .map(|d| d.file_name().and_then(|x| x.to_str()).unwrap().to_string())
        .collect::<Vec<_>>();

    pkgs.sort();

    Ok(pkgs)
}

fn get_package_dir() -> CompResult<PathBuf> {
    Ok(files::get_texmf_loc()?.join("tex").join("latex"))
}
