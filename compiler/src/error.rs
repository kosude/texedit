/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::process::exit;

pub type CompResult<T> = Result<T, CompError>;

pub enum CompError {
    FilesystemError(String),
    FileNotFoundError(String),
    CompilationError(String),
    WatchStartUpError(String),
    WatchRuntimeError(String),
}

impl CompError {
    pub fn handle(self) -> ! {
        match &self {
            Self::FilesystemError(s) => eprintln!("Filesystem error: {}", s),
            Self::FileNotFoundError(s) => eprintln!("File not found: {}", s),
            Self::CompilationError(s) => eprintln!("TeX compilation error: {}", s),
            Self::WatchStartUpError(s) => eprintln!("Error on watch service start-up: {}", s),
            Self::WatchRuntimeError(s) => eprintln!("Error during watch service runtime: {}", s),
        };
        exit(i32::from(self));
    }
}

impl From<CompError> for i32 {
    fn from(value: CompError) -> Self {
        match value {
            CompError::FilesystemError(_) => 1,
            CompError::FileNotFoundError(_) => 2,
            CompError::CompilationError(_) => 3,
            CompError::WatchStartUpError(_) => 4,
            CompError::WatchRuntimeError(_) => 5,
        }
    }
}
