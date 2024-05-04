/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__resources_hpp__
#define __texedit__resources_hpp__

#include <wx/string.h>
#include <vector>

namespace te::util {
    wxString GetTexeditDir();

    wxString RelToExec(const std::vector<wxString> &dirs, const wxString &filename);
    wxString RelToExec(const wxString &filename);

    bool ValidateExecutable(const wxString &path);
}

#endif
