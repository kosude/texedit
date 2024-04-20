/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__editor_panel_hpp__
#define __texedit__editor_panel_hpp__

#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace te {
    class EditorPanel : public wxPanel {
    public:
        EditorPanel(wxWindow *parent);

    private:
        wxBoxSizer *_sizer;
        wxStyledTextCtrl *_stc;
    };
}

#endif
