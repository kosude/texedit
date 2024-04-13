/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__log_hpp__
#define __texedit__log_hpp__

#include <string>

namespace te::util {
    void ResetLogColour();

    void Log(const std::string &msg);
    void Info(const std::string &msg);
    void Warn(const std::string &msg);
    void Error(const std::string &msg);
    void Fatal(const std::string &msg, bool except = true);
}

#endif
