/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// #include "interface/application.hpp"
#include "util/log.hpp"
#include "compile.hpp"

int main(int argc, char **argv) {
    std::string scriptdir = "./";
    std::string outdir = "tmp/";

    te::TeXLiveInstance tex{scriptdir, outdir};
    tex.CompileLaTeX("../tests/test.tex");

    // te::TexEditApplication app{argc, argv};
    // return app.exec();
    return EXIT_SUCCESS;
}
