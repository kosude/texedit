/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "output_pane.hpp"

namespace te::gui {
    OutputPane::OutputPane(wxWindow *parent) : PaneBase{parent} {
        _listbox = new wxListBox(this, wxID_ANY);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_listbox, 1, wxEXPAND);
        SetSizer(_sizer);
    }
}
