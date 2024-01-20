/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "util/log.hpp"
#include "compile.hpp"

int main(int argc, char **argv) {
    std::string scriptdir = "scripts/";
    std::string outdir = "pdftmp/";

    te::TeXLiveInstance tex{scriptdir, outdir};
    tex.CompileLaTeX("../tests/test.tex");

    return 0;
}
