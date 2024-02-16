/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#![allow(dead_code)]

use colored::Colorize;

use std::fmt::Display;

pub fn info<S: Into<String> + Display>(str: S) {
    println!("{str}");
}

pub fn error<S: Into<String> + Display>(str: S) {
    eprintln!("{} {str}", "error:".red().bold());
}

pub fn fatal<S: Into<String> + Display>(str: S) {
    eprintln!("{} {}", "fatal:".red().bold(), str.to_string().red());
}
