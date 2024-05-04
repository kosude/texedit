/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "layout/panes/output_pane.hpp"
#include "layout/panes/preview_pane.hpp"
#include "process/services/compiler_process.hpp"
#include "process/services/pdf_server_process.hpp"
#include "process/process.hpp"
#include "command_ids.hpp"
#include "prog_info.hpp"

#include <wx/aboutdlg.h>
#include <wx/splitter.h>

namespace te::gui {
    MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1280, 720}}, _proc_mgr{this}, _layout{this} {
        BuildMenuBar();

        // use logger for message redirects
        _logger = new util::GlobalLogger(_layout.GetOutputPane()->GetListBox());
        wxLog::SetActiveTarget(_logger);

        _compiler_proc = _proc_mgr.ExecuteAsync<proc::CompilerProcess>();
        _preview_proc = _proc_mgr.ExecuteAsync<proc::PDFServerProcess>();
        _preview_proc->OnPortFound([&](long p) {
            _layout.GetPreviewPane()->Load(wxString::Format("http://localhost:%li", p));
        });
    }

    MainFrame::~MainFrame() {
        // reset logging to default behaviour before deleting the logger object
        wxLog::SetActiveTarget(nullptr);
        delete _logger;
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
        wxString sc = _compiler_proc->ReadLineStdout();
        if (!sc.IsEmpty()) {
            wxLogStatus(sc);
        }

        wxString sp = _preview_proc->ReadLineStdout();
        if (!sp.IsEmpty()) {
            wxLogStatus(sp);
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
