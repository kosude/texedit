/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "root_frame.hpp"

#include "util/url_open.hpp"
#include "util/log.hpp"

namespace te {
    RootFrame::RootFrame() : wxFrame(nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1080, 720}), _menuBar{this} {
        // initialise and apply menu bar
        SetMenuBar(_menuBar.component);
    }

    RootFrame::MenuBar::MenuBar(RootFrame *frame): component{new wxMenuBar}, _frame{frame} {
        //
        // File menu

        wxMenu *file = new wxMenu;
        file->Append(wxID_EXIT);

        component->Append(file, "&File");
        _frame->Bind(wxEVT_MENU, [=](wxCommandEvent &) { _OnFileExit(); }, wxID_EXIT);

        //
        // Help menu

        wxMenu *help = new wxMenu;
        help->Append(_ID_OPEN_REPOSITORY, "Git &repository...");

        component->Append(help, "&Help");
        _frame->Bind(wxEVT_MENU, [=](wxCommandEvent &) { _OnHelpGitRepository(); }, _ID_OPEN_REPOSITORY);
    }

    void RootFrame::MenuBar::_OnFileExit() {
        _frame->Close(true);
    }

    void RootFrame::MenuBar::_OnHelpGitRepository() {
        util::OpenUrl(util::GitHubUrl);
    }
}
