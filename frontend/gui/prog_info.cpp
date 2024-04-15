/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "prog_info.hpp"

namespace te {
    wxAboutDialogInfo ProgInfo::GenerateAboutDialogInfo() {
        wxAboutDialogInfo info;
        info.SetName(name);
        info.SetVersion(version);
        info.SetDescription(description);
        info.SetCopyright(copyright);
        info.SetWebSite(website);
        info.SetLicence(licence);

        return info;
    }
}
