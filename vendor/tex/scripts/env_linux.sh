base=$1

export PATH="$PATH:$(realpath "$base/bin/linux")"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$(realpath "$base/lib/linux")"
