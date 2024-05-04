/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "process/services/compiler_process.hpp"
#include "process/services/pdf_server_process.hpp"
#include "process/process.hpp"
#include "command_ids.hpp"
#include "editor_panel.hpp"
#include "explorer_panel.hpp"
#include "prog_info.hpp"

#include <wx/aboutdlg.h>
#include <wx/splitter.h>

namespace te::gui {
    MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1024, 640}}, _proc_mgr{this} {
        BuildMenuBar();
        BuildSplitLayout();

        // use logger for message redirects
        _logger = new util::GlobalLogger(_lb);
        wxLog::SetActiveTarget(_logger);

        _compiler_proc = _proc_mgr.ExecuteAsync<proc::CompilerProcess>();
        _preview_proc = _proc_mgr.ExecuteAsync<proc::PDFServerProcess>();
        _preview_proc->OnPortFound([&](long p) {
            _preview->Load(wxString::Format("http://localhost:%li", p));
        });

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
        //          |
        // Explorer | Editor, preview, etc
        //          |
        wxSplitterWindow *left_split = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        left_split->SetMinimumPaneSize(100);
        wxWindow *explorer_pane = new wxWindow(left_split, wxID_ANY);
        wxWindow *non_explorer_nested = new wxWindow(left_split, wxID_ANY);
        left_split->SplitVertically(explorer_pane, non_explorer_nested);

        //        |
        // Editor | Preview etc
        //        |
        wxSplitterWindow *middle_split = new wxSplitterWindow(non_explorer_nested, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        middle_split->SetMinimumPaneSize(200);
        wxWindow *editor_pane = new wxWindow(middle_split, wxID_ANY);
        wxWindow *non_editor_nested = new wxWindow(middle_split, wxID_ANY);
        middle_split->SplitVertically(editor_pane, non_editor_nested);

        //     Preview
        // ----------------
        //  Output console
        wxSplitterWindow *right_hoz_split = new wxSplitterWindow(non_editor_nested, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
        right_hoz_split->SetMinimumPaneSize(200);
        wxWindow *preview_pane = new wxWindow(right_hoz_split, wxID_ANY);
        wxWindow *console_pane = new wxWindow(right_hoz_split, wxID_ANY);
        right_hoz_split->SplitHorizontally(preview_pane, console_pane);

        // Explorer
        ExplorerPanel *explorer = new ExplorerPanel(explorer_pane);
        wxBoxSizer *explorer_sizer = new wxBoxSizer(wxVERTICAL);
        explorer_pane->SetSizer(explorer_sizer);
        explorer_sizer->Add(explorer, 1, wxEXPAND);
        wxBoxSizer *non_explorer_sizer = new wxBoxSizer(wxVERTICAL);
        non_explorer_nested->SetSizer(non_explorer_sizer);
        non_explorer_sizer->Add(middle_split, 1, wxEXPAND);

        // Editor
        EditorPanel *editor = new EditorPanel(editor_pane);
        wxBoxSizer *editor_sizer = new wxBoxSizer(wxVERTICAL);
        editor_pane->SetSizer(editor_sizer);
        editor_sizer->Add(editor, 1, wxEXPAND);
        wxBoxSizer *non_editor_sizer = new wxBoxSizer(wxVERTICAL);
        non_editor_nested->SetSizer(non_editor_sizer);
        non_editor_sizer->Add(right_hoz_split, 1, wxEXPAND);

        // Preview
        _preview = new PreviewPanel(preview_pane);
        wxBoxSizer *preview_sizer = new wxBoxSizer(wxVERTICAL);
        preview_pane->SetSizer(preview_sizer);
        preview_sizer->Add(_preview, 1, wxEXPAND);

        // Console (listbox)
        _lb = new wxListBox(console_pane, wxID_ANY);
        wxBoxSizer *console_sizer = new wxBoxSizer(wxVERTICAL);
        console_pane->SetSizer(console_sizer);
        console_sizer->Add(_lb, 1, wxEXPAND);

        //
        // Root sizer
        //
        wxBoxSizer *root = new wxBoxSizer(wxHORIZONTAL);
        root->Add(left_split, 1, wxEXPAND);
        SetSizer(root);
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
