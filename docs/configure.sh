#!/usr/bin/env bash

SPHINXEXEC=$1
SRCDIR=$2
BINDIR=$3
UTILDIR=$4
VERSION=$5

CMD="$SPHINXEXEC -q -b html $SRCDIR $BINDIR"

echo -e "\t(configure.sh): $CMD" # for diagnostics (particularly in CD pipelines)

# run sphinx-build with env vars set
CONFPY_VERSION=$VERSION \
$CMD
