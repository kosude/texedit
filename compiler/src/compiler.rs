/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use std::{
    path::{Path, PathBuf},
    process::Command,
};

use crate::error::{CompError, CompResult};

#[derive(Clone)]
pub struct Compiler<'a> {
    texpdfc: &'a PathBuf,
    texdoc: PathBuf,
    outdir: PathBuf,
}

impl<'a> Compiler<'a> {
    pub fn new(p: &'a PathBuf) -> Self {
        Self {
            texpdfc: p,
            texdoc: PathBuf::default(),
            outdir: PathBuf::default(),
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

    pub fn compile(&mut self) -> CompileResult {
        let mut cmd = Command::new(self.texpdfc);
        if cfg!(target_os = "macos") {
            cmd.arg("darwin");
        } else if cfg!(unix) {
            cmd.arg("linux");
        }
        cmd.args([&self.texdoc, &self.outdir]);

        println!("\"{}\"", format!("{:?}", cmd).replace("\"", ""));

        cmd.status()
            .unwrap()
            .success()
            .then(|| ())
            .ok_or(CompError::CompilationError(
                "texpdfc compilation failed".to_string(),
            ))?;

        Ok(CompileOutput::new(self.build_output_path_stem()))
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
