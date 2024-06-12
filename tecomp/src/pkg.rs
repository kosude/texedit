/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use crate::error::CompResult;

pub fn get_installed() -> CompResult<Vec<String>> {
    // TODO: abstract over `tlmgr list --only-installed`
    todo!()
}
