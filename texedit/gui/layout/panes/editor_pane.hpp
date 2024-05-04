/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__editor_pane_hpp__
#define __texedit__editor_pane_hpp__

#include <wx/wx.h>
#include <wx/stc/stc.h>
#include "pane_base.hpp"

namespace te::gui {
    class EditorPane : public PaneBase {
    public:
        EditorPane(wxWindow *parent);

    private:
        wxBoxSizer *_sizer;
        wxStyledTextCtrl *_stc;
    };
}

#endif
