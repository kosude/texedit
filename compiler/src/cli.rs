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

#[derive(Args, Debug)]
pub struct CommonArgGroup {
    /// Path to the input .tex file
    pub input: String,

    /// Path to output directory
    #[arg(short, long, default_value = ".")]
    pub outdir: String,
    /// Print full TeX compilation output
    #[arg(short, long, action)]
    pub verbose: bool,
}

/// Compile TeX input into PDF output
#[derive(Args, Debug)]
pub struct MakeArgs {
    #[command(flatten)]
    pub com: CommonArgGroup,
}

/// Persistently watch folder or file for changes and recompile
#[derive(Args, Debug)]
pub struct WatchArgs {
    /// Path to a file or directory to watch
    pub watch: String,

    #[command(flatten)]
    pub com: CommonArgGroup,
}
