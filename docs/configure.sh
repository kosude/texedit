#!/usr/bin/env bash

SPHINXEXEC=$1
SRCDIR=$2
BINDIR=$3
UTILDIR=$4

CMD="$SPHINXEXEC -q -b html $SRCDIR $BINDIR"

echo -e "\t(configure.sh): $CMD" # for diagnostics (particularly in CD pipelines)

# run sphinx-build with env vars set
CONFPY_VERSION="$($UTILDIR/version.sh --short)" \
$CMD
