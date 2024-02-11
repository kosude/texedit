/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::ffi::OsStr;

use crate::log;

pub fn github_url() -> &'static str {
    "https://github.com/kosude/texedit"
}

pub fn open_url(url: impl AsRef<OsStr>) -> bool {
    match open::that(url) {
        Ok(()) => true,
        Err(e) => {
            log::error(e.to_string());
            return false;
        }
    }
}
