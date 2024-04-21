/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "log.hpp"

#include <cio.h>
#include <cioenum.h>
#include <iostream>
#include <ctime>
#include <wx/wx.h>

static wxString GetCurrentDateTime(
    const bool with_time
);

namespace te::util::log {
    void ResetLogColour() {
        ciocolstatedef(stderr);
    }

    void Log(const wxString &msg) {
#       if !defined(NDEBUG)
            std::cerr << "[" << GetCurrentDateTime(true) << "] DEBUG: " << msg << std::endl;
#       endif
    }

    void Info(const wxString &msg) {
        std::cerr << "[" << GetCurrentDateTime(true) << "] " << msg << std::endl;
    }

    void Warn(const wxString &msg) {
        ciocolstateset(CIOCOL_YELLOW, 0xff, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] WARN: " << msg << std::endl;
        ResetLogColour();
    }

    void Error(const wxString &msg, bool show) {
        ciocolstateset(CIOCOL_RED, 0xff, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] ERROR: " << msg << std::endl;
        ResetLogColour();

        if (show) {
            wxLogError(msg.c_str());
        }
    }

    void Fatal(const wxString &msg) {
        ciocolstateset(CIOCOL_RED, 0xff, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] FATAL: " << msg << std::endl;
        ResetLogColour();
    }
}

wxString GetCurrentDateTime(const bool with_time) {
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);

    char buf[64];

    if (tm) {
        if (with_time) {
            std::strftime(buf, 64, "%Y-%m-%d %X", tm);
        } else {
            std::strftime(buf, 64, "%Y-%m-%d", tm);
        }

        return wxString{buf};
    }

    throw std::runtime_error("Date/time get failed");
}
