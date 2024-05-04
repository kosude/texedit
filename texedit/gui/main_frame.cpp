/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "layout/panes/explorer_pane.hpp"
#include "layout/panes/output_pane.hpp"
#include "layout/panes/preview_pane.hpp"
#include "process/services/compiler_process.hpp"
#include "process/services/pdf_server_process.hpp"
#include "process/process.hpp"
#include "command_ids.hpp"
#include "prog_info.hpp"

#include <wx/aboutdlg.h>
#include <wx/generic/dirctrlg.h>
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
        fileMenu->Append(cmds::Menu_OpenFolder, "O&pen Folder...");
        fileMenu->Append(wxID_EXIT, "&Quit");
        menuBar->Append(fileMenu, "&File");

        wxMenu *windowMenu = new wxMenu();
        windowMenu->Append(cmds::Menu_PaneExplorer, "&Explorer");
        windowMenu->Append(cmds::Menu_PanePreview, "PDF &Preview");
        windowMenu->Append(cmds::Menu_PaneOutput, "&Output");
        menuBar->Append(windowMenu, "&Window");

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

    void MainFrame::ShowURL(const wxString &url) {
        if (!wxLaunchDefaultBrowser(url)) {
            wxLogError("Failed to open URL \"%s\"", url);
        }
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

    void MainFrame::OnDirCtrlFileActivated(wxTreeEvent &event) {
        wxGenericDirCtrl dirctrl = _layout.GetExplorerPane()->GetDirCtrl();

        wxLogMessage("%s", dirctrl.GetPath(event.GetItem()));
    }

    void MainFrame::OnButtonOpenFolder(wxCommandEvent &event) {
        wxDirDialog dlg(this, "Choose a workspace directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        if (dlg.ShowModal() == wxID_CANCEL) {
            return;
        }

        _layout.GetExplorerPane()->ChangeRootDir(dlg.GetPath());
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

    void MainFrame::OnMenuPaneExplorer(wxCommandEvent &event) {
        _layout.ShowExplorerPane();
    }
    void MainFrame::OnMenuPaneOutput(wxCommandEvent &event) {
        _layout.ShowOutputPane();
    }
    void MainFrame::OnMenuPanePreview(wxCommandEvent &event) {
        _layout.ShowPreviewPane();
    }

    wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
        EVT_IDLE(MainFrame::OnIdle)

        EVT_DIRCTRL_FILEACTIVATED(wxID_ANY, MainFrame::OnDirCtrlFileActivated)
        EVT_BUTTON(cmds::Button_OpenFolder, MainFrame::OnButtonOpenFolder)
        EVT_MENU(cmds::Menu_OpenFolder,     MainFrame::OnButtonOpenFolder)

        EVT_MENU(wxID_EXIT,  MainFrame::OnMenuQuit)
        EVT_MENU(wxID_ABOUT, MainFrame::OnMenuAbout)
        EVT_MENU(cmds::Menu_URLSourcePage,      MainFrame::OnMenuURLSourcePage)
        EVT_MENU(cmds::Menu_URLFeatureRequest,  MainFrame::OnMenuURLFeatureRequest)
        EVT_MENU(cmds::Menu_URLBugReport,       MainFrame::OnMenuURLBugReport)
        EVT_MENU(cmds::Menu_URLUserManual,      MainFrame::OnMenuURLUserManual)
        EVT_MENU(cmds::Menu_PaneExplorer,       MainFrame::OnMenuPaneExplorer)
        EVT_MENU(cmds::Menu_PaneOutput,         MainFrame::OnMenuPaneOutput)
        EVT_MENU(cmds::Menu_PanePreview,        MainFrame::OnMenuPanePreview)
    wxEND_EVENT_TABLE()
}
