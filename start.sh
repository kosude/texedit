#!/usr/bin/env bash

# WARNING: EXECUTE THIS SCRIPT DIRECTLY! -- DO NOT RUN WITH THE 'SOURCE' COMMAND

base_dir="$(realpath "${0%/*}")" # this should be the build/install location of texedit
lib_dir=$base_dir/lib

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$lib_dir

exec $base_dir/texedit
