/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use clap::{Args, Parser, Subcommand};

#[derive(Parser, Debug)]
#[command(about, long_about = None)]
pub struct Cli {
    #[command(subcommand)]
    pub subcommand: CommandVariant,
}

#[derive(Subcommand, Debug)]
pub enum CommandVariant {
    Make(MakeArgs),
    Watch(WatchArgs),
    Pkg(PkgArgs),
}

#[derive(Args, Debug)]
pub struct CommonArgGroup {
    /// Path to the input .tex file
    pub input: String,

    /// Path to output directory
    #[arg(short, long, default_value = ".")]
    pub outdir: String,
    /// Print full TeX compilation output
    #[arg(short, long)]
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

    /// Initially compile the document when watch is started
    #[arg(short = 'i', long)]
    pub initial_make: bool,

    #[command(flatten)]
    pub com: CommonArgGroup,
}

/// Manage LaTeX packages under the tecomp texmf directory
#[derive(Args, Debug)]
#[command(arg_required_else_help = true)]
pub struct PkgArgs {
    /// List installed packages
    #[arg(long)]
    pub list: bool,
}
