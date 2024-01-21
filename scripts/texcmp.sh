#!/usr/bin/env bash

# WARNING: EXECUTE THIS SCRIPT DIRECTLY - DO NOT RUN WITH THE 'SOURCE' COMMAND

usage() {
    cat << EOF
usage: texcmp.sh (nix/osx) TEXNAME OUTDIR

nix - Use Unix/Linux binaries for TeX compilation
osx - Use macOS binaries for TeX compilation
EOF
}

if [ $# -ne 3 ] ; then
    echo Error: malformed syntax
    usage
    exit 1
fi

arch=$1
filename=$(realpath "$2")
outdir=$(realpath "$3")

base_dir="$(realpath "${0%/*}/..")"
texlive_dir="$(realpath "$base_dir/texlive/$arch")"
pdflatex_bin="$texlive_dir/pdflatex"

cd $texlive_dir

echo $pdflatex_bin -output-directory=$outdir $filename

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$texlive_dir/lib"
$pdflatex_bin -output-directory=$outdir $filename
