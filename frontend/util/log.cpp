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

static std::string GetCurrentDateTime(
    const bool with_time
);

namespace te::util {
    void ResetLogColour() {
        ciocolstatedef(stderr);
    }

    void Log(const std::string &msg) {
#       if !defined(NDEBUG)
            std::cerr << "[" << GetCurrentDateTime(true) << "] DEBUG: " << msg << std::endl;
#       endif
    }

    void Info(const std::string &msg) {
        std::cerr << "[" << GetCurrentDateTime(true) << "] " << msg << std::endl;
    }

    void Warn(const std::string &msg) {
        ciocolstateset(CIOCOL_YELLOW, 0xff, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] WARN: " << msg << std::endl;
        ResetLogColour();
    }

    void Error(const std::string &msg) {
        ciocolstateset(CIOCOL_RED, 0xff, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] ERROR: " << msg << std::endl;
        ResetLogColour();
    }

    void Fatal(const std::string &msg, bool except) {
        ciocolstateset(CIOCOL_RED, CIOCOL_YELLOW, stderr);
        std::cerr << "[" << GetCurrentDateTime(true) << "] FATAL: " << msg << std::endl;
        ResetLogColour();

        if (except) {
            throw new std::runtime_error(msg);
        }
    }
}

std::string GetCurrentDateTime(const bool with_time) {
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);

    char buf[64];

    if (tm) {
        if (with_time) {
            std::strftime(buf, 64, "%Y-%m-%d %X", tm);
        } else {
            std::strftime(buf, 64, "%Y-%m-%d", tm);
        }

        return std::string { buf };
    }

    throw std::runtime_error("Date/time get failed");
}
