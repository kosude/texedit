/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use clap::{Args, Parser, Subcommand};

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Cli {
    #[command(subcommand)]
    pub subcommand: CommandVariant,
}

#[derive(Subcommand, Debug)]
pub enum CommandVariant {
    Make(MakeArgs),
    Watch(WatchArgs),
}

/// Compile TeX input into PDF output
#[derive(Args, Debug)]
pub struct MakeArgs {
    /// Path to the input .tex file
    pub input: String,
    /// Path to output directory
    #[arg(short, long, default_value = ".")]
    pub outdir: String,
}

/// Persistently watch folder or file for changes and recompile
#[derive(Args, Debug)]
pub struct WatchArgs {
    /// Path to a file or directory to watch
    pub watch: String,

    /// Path to the input .tex file
    pub input: String,
    /// Path to output directory
    #[arg(short, long, default_value = ".")]
    pub outdir: String,
}
