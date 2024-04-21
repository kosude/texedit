/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__log_hpp__
#define __texedit__log_hpp__

#include <wx/string.h>

namespace te::util::log {
    void ResetLogColour();

    void Log(const wxString &msg);
    void Info(const wxString &msg);
    void Warn(const wxString &msg);
    void Error(const wxString &msg, bool show = true);
    void Fatal(const wxString &msg);
}

#endif
