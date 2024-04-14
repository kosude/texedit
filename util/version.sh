#!/usr/bin/env bash

function getverslong {
    echo "$($GIT describe --abbrev=4 --always --tags --dirty 2>/dev/null)"
}
function getversshort {
    s="$($GIT describe --abbrev=4 --always --tags --dirty 2>/dev/null)"
    echo "${s%-g*}"
}

GIT="$(command -v git)"

OUT=
NO_V=

for arg in "$@"; do
    case "$arg" in
        --long)
            OUT="$(getverslong)"
            ;;
        --short)
            OUT="$(getversshort)"
            if [ "$?" != 0 ]; then
                OUT="v0.0.0"
            fi
            ;;
        --no-v)
            NO_V=true
            ;;
    esac
done

if [ ! -n "$OUT" ]; then
    OUT="$(getverslong)"
fi

if [ -n "$NO_V" ]; then
    OUT="${OUT/v}"
fi

echo $OUT
