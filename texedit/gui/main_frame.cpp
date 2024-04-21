/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "process/process.hpp"
#include "util/resources.hpp"
#include "command_ids.hpp"
#include "editor_panel.hpp"
#include "preview_panel.hpp"
#include "prog_info.hpp"

#include <wx/aboutdlg.h>
#include <wx/splitter.h>

namespace te::gui {
    MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1024, 640}}, _proc_mgr{this}, _tecomp{_proc_mgr} {
        BuildMenuBar();
        BuildSplitLayout();

        // use logger for message redirects
        _logger = new util::GlobalLogger(_lb);
        wxLog::SetActiveTarget(_logger);

        _tecomp.Start();

        wxLogDebug("TEST DEBUG");
        wxLogInfo("TEST INFO");
        wxLogStatus("TEST STATUS");
        wxLogMessage("TEST MESSAGE");
        wxLogWarning("TEST WARNING");
        wxLogError("TEST ERROR");
    }

    MainFrame::~MainFrame() {
        // reset logging to default behaviour before deleting the logger object
        wxLog::SetActiveTarget(nullptr);
        delete _logger;
    }

    void MainFrame::BuildSplitLayout() {
        wxSplitterWindow *hsplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        hsplitter->SetMinimumPaneSize(100);

        wxWindow *t = new wxWindow(hsplitter, wxID_ANY);

        wxSplitterWindow *vsplitter = new wxSplitterWindow(t, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        vsplitter->SetMinimumPaneSize(100);
        wxWindow *l = new wxWindow(vsplitter, wxID_ANY);
        wxBoxSizer* lSizer = new wxBoxSizer(wxVERTICAL);
        lSizer->Add(new EditorPanel(l), 1, wxEXPAND);
        l->SetSizer(lSizer);
        wxWindow *r = new wxWindow(vsplitter, wxID_ANY);
        wxBoxSizer* rSizer = new wxBoxSizer(wxVERTICAL);
        rSizer->Add(new PreviewPanel(r), 1, wxEXPAND);
        r->SetSizer(rSizer);
        vsplitter->SplitVertically(l, r);
        wxBoxSizer *tSizer = new wxBoxSizer(wxVERTICAL);
        tSizer->Add(vsplitter, 1, wxEXPAND);
        t->SetSizer(tSizer);

        wxWindow *b = new wxWindow(hsplitter, wxID_ANY);
        wxBoxSizer *bSizer = new wxBoxSizer(wxVERTICAL);
        _lb = new wxListBox(b, wxID_ANY);
        bSizer->Add(_lb, 1, wxEXPAND);
        b->SetSizer(bSizer);

        hsplitter->SplitHorizontally(t, b);

        wxBoxSizer *rootSizer = new wxBoxSizer(wxHORIZONTAL);
        rootSizer->Add(hsplitter, 1, wxEXPAND);
        SetSizer(rootSizer);
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
        helpMenu->AppendSeparator();
        helpMenu->Append(wxID_ABOUT, "&About TexEdit");
        menuBar->Append(helpMenu, "&Help");

        SetMenuBar(menuBar);
    }

    void MainFrame::OnIdle(wxIdleEvent &ev) {
        wxString s = _proc_mgr.PollPipedOutput();
        if (!s.IsEmpty()) {
            wxLogStatus(s);
        }
    }

    void MainFrame::ShowURL(const wxString &url) {
        if (!wxLaunchDefaultBrowser(url)) {
            wxLogError("Failed to open URL \"%s\"", url);
        }
    }

    void MainFrame::OnMenuAbout(wxCommandEvent &event) {
        wxAboutDialogInfo aboutInfo = ProgInfo::GenerateAboutDialogInfo();
        wxAboutBox(aboutInfo);
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
        EVT_IDLE(MainFrame::OnIdle)
        EVT_MENU(wxID_EXIT, MainFrame::OnMenuQuit)
        EVT_MENU(wxID_ABOUT, MainFrame::OnMenuAbout)
        EVT_MENU(cmds::Menu_URLSourcePage, MainFrame::OnMenuURLSourcePage)
        EVT_MENU(cmds::Menu_URLFeatureRequest, MainFrame::OnMenuURLFeatureRequest)
        EVT_MENU(cmds::Menu_URLBugReport, MainFrame::OnMenuURLBugReport)
        EVT_MENU(cmds::Menu_URLUserManual, MainFrame::OnMenuURLUserManual)
    wxEND_EVENT_TABLE()
}
