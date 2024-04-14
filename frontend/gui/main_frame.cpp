/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "util/except.hpp"
#include "command_ids.hpp"

namespace te {
    MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1080, 720}) {
        BuildMenuBar();
    }

    void MainFrame::BuildMenuBar() {
        _menuBar = new wxMenuBar();

        wxMenu *fileMenu = new wxMenu();
        fileMenu->Append(wxID_EXIT, "&Quit");
        _menuBar->Append(fileMenu, "&File");

        wxMenu *helpMenu = new wxMenu();
        helpMenu->Append(cmds::Menu_URLSourcePage, "Git &repository");
        helpMenu->Append(cmds::Menu_URLFeatureRequest, "&Feature requests");
        helpMenu->Append(cmds::Menu_URLBugReport, "&Bug reports");
        _menuBar->Append(helpMenu, "&Help");

        SetMenuBar(_menuBar);
    }

    void MainFrame::ShowURL(const std::string &url) {
        if (!wxLaunchDefaultBrowser(url)) {
            wxLogError("Failed to open URL \"%s\"", url.c_str());
        }
    }

    void MainFrame::OnMenuQuit(wxCommandEvent &event) {
        Close(true);
    }

    void MainFrame::OnMenuURLSourcePage(wxCommandEvent &event) {
        ShowURL("https://github.com/kosude/texedit");
    }

    void MainFrame::OnMenuURLFeatureRequest(wxCommandEvent &event) {
        ShowURL("https://github.com/kosude/texedit/issues");
    }

    void MainFrame::OnMenuURLBugReport(wxCommandEvent &event) {
        ShowURL("https://github.com/kosude/texedit/issues");
    }

    wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
        EVT_MENU(wxID_EXIT, MainFrame::OnMenuQuit)
        EVT_MENU(cmds::Menu_URLSourcePage, MainFrame::OnMenuURLSourcePage)
        EVT_MENU(cmds::Menu_URLFeatureRequest, MainFrame::OnMenuURLFeatureRequest)
        EVT_MENU(cmds::Menu_URLBugReport, MainFrame::OnMenuURLBugReport)
    wxEND_EVENT_TABLE()
}
