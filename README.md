<img src="res/logo-vec.svg" height=110 align=left>

# TexEdit: a portable, cross-platform editor for TeX documents

[![GitHub](https://img.shields.io/github/license/kosude/texedit)](LICENCE)
![Lines of code](https://www.aschey.tech/tokei/github.com/kosude/texedit)

TexEdit is a graphical application containing a text editor and PDF preview, to make locally editing LaTeX documents easier. Note that a minimal
distribution of TeX including the `pdflatex` binary is included with the program, and so TexEdit is fully portable and does not depend on any existing
TeX installation.

Support for Linux and macOS is confirmed; TexEdit does not currently support Windows, though this may be implemented in the future.

This repository contains both the TexEdit graphical editor as well as the `tecomp` (TexEdit Compiler) backend, which isn't actually a compiler, just
a program to wrap the actual TeX compiler and run the right programs depending on the operating system and architecture.

Note that TexEdit is a personal project that I'm mostly doing for fun, so it likely won't be as finished as a much bigger and more organised project,
for instance. If you want an actual, fully-fledged LaTeX editor, I recommend [Overleaf](https://www.overleaf.com/).


## Documentation

Project documentation, as well as a general user manual, can be found deployed at https://kosude.github.io/texedit. It can also be accessed locally
by building it with `make docs`.

A development TO-DO can be found on [Trello](https://trello.com/b/xtq0vBzz/texedit).
