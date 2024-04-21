/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "resources.hpp"

#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "util/log.hpp"

namespace te::util::res {
    wxString GetTexeditDir() {
        wxFileName f = wxStandardPaths::Get().GetExecutablePath();
        return f.GetPath();
    }

    wxString RelToExec(std::vector<wxString> dirs, wxString filename) {
        wxFileName f = wxFileName::DirName(GetTexeditDir());
        for (auto d : dirs) {
            f.AppendDir(d);
        }

        return f.GetPath() + wxString{wxFileName::GetPathSeparator()} + filename;
    }

    wxString RelToExec(wxString filename) {
        return RelToExec({}, filename);
    }

    bool ValidateExecutable(wxString path) {
        wxFileName f{path};
        return f.FileExists() && f.IsFileExecutable();
    }
}
