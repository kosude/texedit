/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use colored::Colorize;

use std::fmt::Display;

pub fn fatal<S: Into<String> + Display>(str: S) {
    eprintln!("{} {} {str}", "tecomp:".bold(), "fatal:".red().bold());
}
