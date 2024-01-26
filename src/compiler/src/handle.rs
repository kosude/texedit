/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::process::exit;

use crate::{
    error::{CompError, CompResult},
    log,
};

pub fn add_watch_ctrlc_handler() -> CompResult<()> {
    ctrlc::set_handler(|| {
        log::info("Watch session terminated");
        exit(0);
    })
    .map_err(|e| {
        CompError::WatchStartUpError(format!("Interrupt handler setup: {:?}", e.to_string()))
    })?;

    Ok(())
}
