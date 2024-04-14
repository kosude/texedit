/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "util/log.hpp"
#include "util/except.hpp"
#include "command_ids.hpp"
#include "editor_panel.hpp"

#include <wx/splitter.h>

namespace te {
    MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1024, 640}) {
        BuildMenuBar();
        BuildSplitLayout();
    }

    void MainFrame::BuildSplitLayout() {
        wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        splitter->SetMinimumPaneSize(100);

        wxWindow *l = new wxWindow(splitter, wxID_ANY);
        wxBoxSizer* lSizer = new wxBoxSizer(wxHORIZONTAL);
        lSizer->Add(new EditorPanel(l), 1, wxEXPAND);
        l->SetSizer(lSizer);

        wxWindow *r = new wxWindow(splitter, wxID_ANY);
        wxTextCtrl* rText = new wxTextCtrl(r, wxID_ANY, L"Panel 2 Text", wxDefaultPosition, wxSize(150, 150));
        wxBoxSizer* rSizer = new wxBoxSizer(wxHORIZONTAL);
        rSizer->Add(rText, 1, wxEXPAND);
        r->SetSizer(rSizer);

        splitter->SplitVertically(l, r);

        wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
        topSizer->Add(splitter, 1, wxEXPAND);
        SetSizer(topSizer);
    }

    void MainFrame::BuildMenuBar() {
        wxMenuBar *menuBar = new wxMenuBar();

        wxMenu *fileMenu = new wxMenu();
        fileMenu->Append(wxID_EXIT, "&Quit");
        menuBar->Append(fileMenu, "&File");

        wxMenu *helpMenu = new wxMenu();
        helpMenu->Append(cmds::Menu_URLUserManual, "&Documentation");
        helpMenu->AppendSeparator();
        helpMenu->Append(cmds::Menu_URLSourcePage, "Git &Repository");
        helpMenu->Append(cmds::Menu_URLFeatureRequest, "&Feature Requests");
        helpMenu->Append(cmds::Menu_URLBugReport, "&Bug Reports");
        menuBar->Append(helpMenu, "&Help");

        SetMenuBar(menuBar);
    }

    void MainFrame::ShowURL(const std::string &url) {
        if (!wxLaunchDefaultBrowser(url)) {
            util::log::Error("Failed to open URL \"" + url + "\"");
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

    void MainFrame::OnMenuURLUserManual(wxCommandEvent &event) {
        ShowURL("https://kosude.github.io/texedit/");
    }

    wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
        EVT_MENU(wxID_EXIT, MainFrame::OnMenuQuit)
        EVT_MENU(cmds::Menu_URLSourcePage, MainFrame::OnMenuURLSourcePage)
        EVT_MENU(cmds::Menu_URLFeatureRequest, MainFrame::OnMenuURLFeatureRequest)
        EVT_MENU(cmds::Menu_URLBugReport, MainFrame::OnMenuURLBugReport)
        EVT_MENU(cmds::Menu_URLUserManual, MainFrame::OnMenuURLUserManual)
    wxEND_EVENT_TABLE()
}
