/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "editor_panel.hpp"

namespace te::gui {
    EditorPanel::EditorPanel(wxWindow *parent) : wxPanel(parent) {
        _stc = new wxStyledTextCtrl(this, wxID_ANY);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_stc, 1, wxEXPAND);
        SetSizer(_sizer);
    }
}
