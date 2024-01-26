#!/usr/bin/env bash

# This script compiles PDF output from (La)TeX input, on Unix (including Darwin/macOS) systems.
# WARNING: EXECUTE THIS SCRIPT DIRECTLY - DO NOT RUN WITH THE 'SOURCE' COMMAND

usage() {
    cat << EOF
usage: texpdfc.sh (darwin|linux) TEXNAME OUTDIR

darwin - Use macOS binaries for TeX compilation
linux - Use Linux binaries for TeX compilation
EOF
}

if [ $# -ne 3 ] ; then
    echo Error: malformed syntax
    usage
    exit 1
fi

arch=$1
filename=$(realpath $2)
outdir=$(realpath $3)

base_dir="$(realpath "${0%/*}")"
texlive_base_dir="$(realpath "$base_dir/tex")"
texlive_os_dir="$(realpath "$texlive_base_dir/os/$arch")"
pdflatex_bin="$texlive_os_dir/bin/pdflatex"

cd $texlive_base_dir
source env_$arch.sh

cmd="$pdflatex_bin -interaction=nonstopmode -output-directory=$outdir $filename"

echo "$cmd"
$cmd
