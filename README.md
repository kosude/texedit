<p  align=center>
    <img src="res/logo-vec.svg" height=110>
</p>

# TexEdit: a portable, cross-platform editor for TeX documents

TexEdit is a graphical application containing a text editor and PDF preview, to make locally editing LaTeX documents easier. Note that a minimal
distribution of TeX including the `pdflatex` binary is included with the program, and so TexEdit is fully portable and does not depend on any
existing TeX installation.

Support for Linux and macOS is confirmed; TexEdit does not currently support Windows, though this may be implemented in the future.

This repository contains both the TexEdit graphical editor as well as the `tecomp` (TexEdit Compiler) backend, which isn't actually a compiler, just
a program to wrap the actual TeX compiler and run the right programs depending on the operating system and architecture.


## Documentation

Project documentation, as well as a general user manual, can be found deployed at https://kosude.gitlab.io/texedit. It can also be accessed locally
by building it with `make docs`.
