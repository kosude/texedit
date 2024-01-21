/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include <filesystem>

namespace te {
    class TeXLiveInstance {
    public:
        TeXLiveInstance(const std::filesystem::path &scriptdir, const std::filesystem::path &outdir);
        ~TeXLiveInstance();

        void CompileLaTeX(const std::filesystem::path &texname);

    private:
#       if defined(_WIN32)
            static constexpr const char *_TEXCMP_NAME = "texcmp_win32.bat";
#       else
            static constexpr const char *_TEXCMP_NAME = "texcmp.sh";
#       endif

        std::filesystem::path _InvokeTexcmp(const std::filesystem::path &texname) const;

        std::filesystem::path _texcmp;
        std::filesystem::path _outdir;
    };
}
