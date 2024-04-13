/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "root_frame.hpp"

namespace te {
    RootFrame::RootFrame() : wxFrame(nullptr, wxID_ANY, "TexEdit"), _menuBar{this} {
        // initialise and apply menu bar
        SetMenuBar(_menuBar.component);
    }

    RootFrame::MenuBar::MenuBar(RootFrame *frame): _frame{frame} {
        wxMenu *file = new wxMenu;
        file->Append(wxID_EXIT);

        component = new wxMenuBar;
        component->Append(file, "&File");

        _frame->Bind(wxEVT_MENU, [=](wxCommandEvent &) { _OnExit(); }, wxID_EXIT);
    }

    void RootFrame::MenuBar::_OnExit() {
        _frame->Close(true);
    }
}
