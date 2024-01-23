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

#[derive(Args, Debug)]
pub struct ArgsCommon {
    /// Path to output directory
    #[arg(short, long, default_value = ".")]
    pub outdir: String,
}

#[derive(Subcommand, Debug)]
pub enum CommandVariant {
    Make(MakeArgs),
}

/// Compile TeX input into PDF output
#[derive(Args, Debug)]
pub struct MakeArgs {
    /// Path to the input .tex file
    pub input: String,

    #[command(flatten)]
    pub com: ArgsCommon,
}
