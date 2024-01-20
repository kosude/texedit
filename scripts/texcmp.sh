#!/usr/bin/env bash

# WARNING: EXECUTE THIS SCRIPT DIRECTLY - DO NOT RUN WITH THE 'SOURCE' COMMAND

usage() {
    cat << EOF
usage: texcmp.sh (nix/osx/win) TEXNAME

nix - Use Unix/Linux binaries for TeX compilation
osx - Use macOS binaries for TeX compilation
win - Use Windows binaries for TeX compilation
EOF
}

if [ $# -ne 2 ] ; then
    echo Error: malformed syntax
    usage
    exit 1
fi

arch=$1
filename=$(realpath "$2")

base_dir="$(realpath "${0%/*}/..")"
texlive_dir="$(realpath "$base_dir/texlive/$arch")"
pdflatex_bin="$texlive_dir/pdflatex"

cd $texlive_dir

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$texlive_dir/lib"
$pdflatex_bin -output-directory=$base_dir $filename
