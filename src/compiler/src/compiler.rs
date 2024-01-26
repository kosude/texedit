/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use crate::{
    error::{CompError, CompResult},
    log,
};

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum OutputVerbosity {
    /// Full output including pdflatex
    Verbose,
    /// Default value - don't delegate output here from pdflatex; otherwise, full output
    NoDelegation,
}

impl Default for OutputVerbosity {
    fn default() -> Self {
        Self::NoDelegation
    }
}

#[derive(Clone)]
pub struct Compiler<'a> {
    texpdfc: &'a PathBuf,
    texdoc: PathBuf,
    outdir: PathBuf,

    verbosity: OutputVerbosity,
}

impl<'a> Compiler<'a> {
    pub fn new(p: &'a PathBuf) -> Self {
        Self {
            texpdfc: p,
            texdoc: PathBuf::default(),
            outdir: PathBuf::default(),

            verbosity: OutputVerbosity::default(),
        }
    }

    pub fn document(&mut self, path: &Path) -> &mut Self {
        self.texdoc = path.to_path_buf();
        self
    }

    pub fn out_dir(&mut self, path: &Path) -> &mut Self {
        self.outdir = path.to_path_buf();
        self
    }

    pub fn verbosity(&mut self, val: OutputVerbosity) -> &mut Self {
        self.verbosity = val;
        self
    }

    pub fn compile(&self) -> CompileResult {
        let mut cmd = Command::new(self.texpdfc);
        if cfg!(target_os = "macos") {
            cmd.arg("darwin");
        } else if cfg!(unix) {
            cmd.arg("linux");
        }
        cmd.args([&self.texdoc, &self.outdir]);

        log::info(format!("Compiling {:?}", &self.texdoc));

        if self.verbosity == OutputVerbosity::NoDelegation {
            cmd.stdout(Stdio::null());
            cmd.stderr(Stdio::null());
        }

        cmd.status()
            .unwrap()
            .success()
            .then(|| ())
            .ok_or(CompError::CompilationError(
                "texpdfc compilation failed".to_string(),
            ))?;

        let r = CompileOutput::new(self.build_output_path_stem());

        log::info(format!("Resulting PDF is at {:?}", &r.pdf()));

        Ok(r)
    }

    fn build_output_path_stem(&self) -> PathBuf {
        let mut p = self.outdir.clone();
        p.push(self.texdoc.file_stem().unwrap());
        p
    }
}

type CompileResult<'a> = CompResult<CompileOutput>;

#[derive(Default, Debug, Clone)]
pub struct CompileOutput {
    pdf: String,
}

impl CompileOutput {
    pub fn new(p: PathBuf) -> Self {
        Self {
            pdf: Self::construct_extended_path(&p, ".pdf"),
        }
    }

    fn construct_extended_path(p: &PathBuf, ext: &str) -> String {
        p.as_path().display().to_string() + ext
    }

    pub fn pdf(&self) -> &str {
        &self.pdf
    }
}
