/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "editor_pane.hpp"

namespace te::gui {
    EditorPane::EditorPane(wxWindow *parent) : PaneBase(parent) {
        _stc = new wxStyledTextCtrl(this, wxID_ANY);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_stc, 1, wxEXPAND);
        SetSizer(_sizer);
    }
}
