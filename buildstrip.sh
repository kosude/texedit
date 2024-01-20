#!/usr/bin/env bash

usage() {
    cat << EOF
usage: buildstrip.sh BUILDDIR
EOF
}

if [ $# -ne 1 ] ; then
    echo Error: malformed syntax
    usage
    exit 1
fi

build_dir=$1

find $build_dir -name "CMakeFiles" -exec rm -rf {} +
find $build_dir -name "CMakeCache.txt" -exec rm -rf {} +
find $build_dir -name "*.cmake" -exec rm -rf {} +
find $build_dir -name "Makefile" -exec rm -rf {} +
find $build_dir -name "compile_commands.json" -exec rm -rf {} +
