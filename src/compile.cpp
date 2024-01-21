/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "compile.hpp"

#include "util/log.hpp"

namespace te {
    TeXLiveInstance::TeXLiveInstance(const std::filesystem::path &scriptdir, const std::filesystem::path &outdir)
        : _texcmp{scriptdir / _TEXCMP_NAME}, _outdir{outdir} {
    }

    TeXLiveInstance::~TeXLiveInstance() {
    }

    void TeXLiveInstance::CompileLaTeX(const std::filesystem::path &texname) {
        std::filesystem::path out = _InvokeTexcmp(texname);
    }

    std::filesystem::path TeXLiveInstance::_InvokeTexcmp(const std::filesystem::path &texname) const {
        try {
            std::filesystem::create_directory(_outdir);
        } catch (std::exception &e) {
            LERR("Failed to create directory at \"%s\" - exception: %s", _outdir.string().c_str(), e.what());
        }

        std::string cmd = _texcmp;
#       if defined(_APPLE)
            cmd += " osx";
#       elif defined(_UNIX)
            cmd += " nix";
#       endif
        cmd += " \"" + texname.string() + "\" \"" + _outdir.string() + "\"";

        LINFO("Invoking TeX compile script: `%s`", cmd.c_str());

        // TODO - somewhere better to route output for debugging?
        // Also; this obviously isn't very cross-platform. Fix pls!
        std::system(std::string{cmd + ">/dev/null"}.c_str());

        return std::filesystem::path{_outdir / std::string{texname.stem().string() + ".pdf"}};
    }
}
