/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "explorer_panel.hpp"

namespace te::gui {
    ExplorerPanel::ExplorerPanel(wxWindow *parent) : wxPanel(parent) {
        _dirctl = new wxGenericDirCtrl(this, wxID_ANY);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_dirctl, 1, wxEXPAND);
        SetSizer(_sizer);
    }
}
