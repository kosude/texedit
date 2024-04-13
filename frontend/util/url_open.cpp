/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "url_open.hpp"

#include "log.hpp"

#include <cstdlib>

namespace te::util {
    void OpenUrl(const std::string &url) {
        std::string cmd;

        // supposedly this is cross-platform enough (though I am a little uncomfy with the reliance on xdg-utils being installed on Linux)
#       if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            cmd = "start ";
#       elif defined(__APPLE__)
            cmd = "open ";
#       elif defined(__linux__)
            cmd = "xdg-open ";
#       else
#           error Invalid configuration
#       endif

        cmd += url;

        Info("Opening URL: executing: " + cmd);

        std::system(cmd.c_str());
    }
}
