/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "prog_info.hpp"

namespace te::gui {
    wxAboutDialogInfo ProgInfo::GenerateAboutDialogInfo() {
        wxAboutDialogInfo info;
        info.SetName(name);
        info.SetVersion(version);
        info.SetDescription(description);
        info.SetCopyright(copyright);
        info.SetWebSite(website);

        return info;
    }
}
