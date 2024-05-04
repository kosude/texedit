/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "resources.hpp"

#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/stdpaths.h>

namespace te::util {
    wxString GetTexeditDir() {
        wxFileName f = wxStandardPaths::Get().GetExecutablePath();
        return f.GetPath();
    }

    wxString RelToExec(const std::vector<wxString> &dirs, const wxString &filename) {
        wxFileName f = wxFileName::DirName(GetTexeditDir());
        for (auto d : dirs) {
            f.AppendDir(d);
        }

        return f.GetPath() +
               wxFileName::GetPathSeparator() +
               filename;
    }

    wxString RelToExec(const wxString &filename) {
        return RelToExec({}, filename);
    }

    bool ValidateExecutable(const wxString &path) {
        wxFileName f{path};
        return f.FileExists() && f.IsFileExecutable();
    }
}
