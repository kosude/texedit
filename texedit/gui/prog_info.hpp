/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__about_dialogue_hpp__
#define __texedit__about_dialogue_hpp__

#include <wx/aboutdlg.h>

namespace te::gui {
    class ProgInfo {
    public:
        static constexpr const char *name = "TexEdit";
        static constexpr const char *version = TEXEDIT_VERSION;
        static constexpr const char *description = "Integrated viewer, compiler and editor for TeX documents";
        static constexpr const char *copyright = "(c) 2024 Jack Bennett";
        static constexpr const char *website = "https://kosude.gitlab.io/texedit/";

        static wxAboutDialogInfo GenerateAboutDialogInfo();
    };
}

#endif
