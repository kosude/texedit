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
    std::string GetTexeditDir() {
        wxFileName f = wxStandardPaths::Get().GetExecutablePath();
        return f.GetPath().ToStdString();
    }

    std::string RelToExec(std::vector<std::string> dirs, std::string filename) {
        wxFileName f = wxFileName::DirName(GetTexeditDir());
        for (auto d : dirs) {
            f.AppendDir(d);
        }

        return f.GetPath().ToStdString() + wxString{wxFileName::GetPathSeparator()}.ToStdString() + filename;
    }

    std::string RelToExec(std::string filename) {
        return RelToExec({}, filename);
    }

    bool ValidateExecutable(std::string path) {
        wxFileName f{path};
        return f.FileExists() && f.IsFileExecutable();
    }
}
