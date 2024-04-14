<img src="res/logo-vec.svg" height=110 align=left>

# TexEdit: a portable, cross-platform editor for TeX documents

TexEdit is a graphical application containing a text editor and PDF preview, to make locally editing LaTeX documents easier. Note that a minimal
distribution of TeX including the `pdflatex` binary is included with the program, and so TexEdit is fully portable and does not depend on any existing
TeX installation.

Support for Linux and macOS is confirmed; TexEdit does not currently support Windows, though this may be implemented in the future.

This repository contains both the TexEdit graphical editor as well as the `tecomp` (TexEdit Compiler) backend, which isn't actually a compiler, just
a program to wrap the actual TeX compiler and run the right programs depending on the operating system and architecture.

Note that TexEdit is a personal project that I'm mostly doing for fun, so it likely won't be as finished as a much bigger and more organised project,
for instance. If you want an actual, fully-fledged LaTeX editor, I recommend [Overleaf](https://www.overleaf.com/).
