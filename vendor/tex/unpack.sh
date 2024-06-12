#!/usr/bin/env bash

# This script neatly extracts the TeX distribution archive into the specified output directory
# WARNING: EXECUTE THIS SCRIPT DIRECTLY - DO NOT RUN WITH THE 'SOURCE' COMMAND

usage() {
    cat << EOF
usage: unpack.sh OUTDIR
EOF
}

if [ $# -ne 1 ] ; then
    echo Error: malformed syntax
    usage
    exit 1
fi

src_dir="$(realpath "${0%/*}")"
dst_dir="$(realpath "$1")"

if [ ! -d "$dst_dir" ]; then
    echo Error: Output directory not found at path $dst_dir
    exit 1
fi

archive="$src_dir/tex.tar.xz"

if [ ! -f "$archive" ]; then
    echo Error: TeX distribution archive not found at path $archive
    exit 1
fi

echo Extracting bundled TeX distribution into $dst_dir...

# extract archive
tar -xJf $archive -C $dst_dir

# copy scripts
cp -r "$src_dir/scripts/." "$dst_dir"
