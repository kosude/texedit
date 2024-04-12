/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::process::exit;

use crate::log;

pub type CompResult<T> = Result<T, CompError>;

pub enum CompError {
    FilesystemError(String),
    FileNotFoundError(String),
    CompilationError(String),
    WatchStartUpError(String),
    WatchRuntimeError(String),
}

impl CompError {
    fn base_handle_fn(&self, c: &i32) {
        match &self {
            Self::FilesystemError(s) => log::fatal(format!("Filesystem error (error {c}): {s}")),
            Self::FileNotFoundError(s) => log::fatal(format!("File not found (error {c}): {s}")),
            Self::CompilationError(s) => {
                log::fatal(format!("TeX compilation error (error {c}): {s}"))
            }
            Self::WatchStartUpError(s) => {
                log::fatal(format!("Error on watch service start-up (error {c}): {s}"))
            }
            Self::WatchRuntimeError(s) => log::fatal(format!(
                "Error during watch service runtime (error {c}): {s}"
            )),
        };
    }

    pub fn handle(self) -> ! {
        let c = i32::from(&self);
        self.base_handle_fn(&c);

        exit(c);
    }

    pub fn handle_safe(self) {
        let c = i32::from(&self);
        self.base_handle_fn(&c);
    }
}

impl From<&CompError> for i32 {
    fn from(value: &CompError) -> Self {
        match value {
            CompError::FilesystemError(_) => 1,
            CompError::FileNotFoundError(_) => 2,
            CompError::CompilationError(_) => 3,
            CompError::WatchStartUpError(_) => 4,
            CompError::WatchRuntimeError(_) => 5,
        }
    }
}
