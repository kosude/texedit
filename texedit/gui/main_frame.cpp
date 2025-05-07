/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main_frame.hpp"

#include "common/dialogues.hpp"
#include "layout/panes/explorer_pane.hpp"
#include "layout/panes/output_pane.hpp"
#include "layout/panes/preview_pane.hpp"
#include "process/services/compiler_process.hpp"
#include "process/process.hpp"
#include "prog_info.hpp"

#include <wx/aboutdlg.h>
#include <wx/generic/dirctrlg.h>
#include <wx/splitter.h>

enum {
    Menu_URLSourcePage = wxID_HIGHEST + 1,
    Menu_URLFeatureRequest,
    Menu_URLBugReport,
    Menu_URLUserManual,
    Menu_PaneExplorer,
    Menu_PaneOutput,
    Menu_PanePreview,
    Menu_OpenFolder,
    Menu_OpenFile,
    Menu_SaveFile,
    Menu_SaveFileAs,
    Menu_CloseFolder,
    Menu_CloseEditor,
};

namespace te::gui {
    MainFrame::MainFrame() : wxFrame{nullptr, wxID_ANY, "TexEdit", wxDefaultPosition, wxSize{1280, 720}}, _proc_mgr{this}, _layout{this} {
        BuildMenuBar();

        // use logger for message redirects
        _logger = std::make_unique<util::GlobalLogger>(_layout.GetOutputPane()->GetListBox());
        wxLog::SetActiveTarget(_logger.get());

        // TODO: temp --
        _layout.GetPreviewPane()->SetPDFLocation("HelloWorld.pdf");
        // _layout.GetPreviewPane()->SetPDFLocation("/home/jack/Downloads/7-stripe-rainbow-pride-flag-A4-size.pdf");

        _compiler_proc = _proc_mgr.ExecuteAsync<proc::CompilerProcess>();
    }

    MainFrame::~MainFrame() {
        // reset logging to default behaviour before deleting the logger object
        wxLog::SetActiveTarget(nullptr);
    }

    void MainFrame::BuildMenuBar() {
        wxMenuBar *menuBar = new wxMenuBar();

        wxMenu *fileMenu = new wxMenu();
        fileMenu->Append(Menu_OpenFile, "&Open File...\tCtrl+O");
        fileMenu->Append(Menu_OpenFolder, "Open &Folder...\tCtrl+Shift+O");
        fileMenu->AppendSeparator();
        fileMenu->Append(Menu_SaveFile, "&Save\tCtrl+S");
        fileMenu->Append(Menu_SaveFileAs, "&Save As...\tCtrl+Shift+S");
        fileMenu->AppendSeparator();
        fileMenu->Append(Menu_CloseFolder, "&Close Folder");
        fileMenu->Append(Menu_CloseEditor, "&Close Editor\tCtrl+W");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_EXIT, "&Quit");
        menuBar->Append(fileMenu, "&File");

        wxMenu *viewMenu = new wxMenu();
        viewMenu->Append(Menu_PaneExplorer, "&Explorer\tCtrl+Alt+E");
        viewMenu->Append(Menu_PanePreview, "PDF &Preview\tCtrl+Alt+P");
        viewMenu->Append(Menu_PaneOutput, "&Output\tCtrl+Alt+O");
        menuBar->Append(viewMenu, "&View");

        wxMenu *helpMenu = new wxMenu();
        helpMenu->Append(Menu_URLUserManual, "&Documentation");
        helpMenu->AppendSeparator();
        helpMenu->Append(Menu_URLSourcePage, "Git &Repository");
        helpMenu->Append(Menu_URLFeatureRequest, "&Feature Requests");
        helpMenu->Append(Menu_URLBugReport, "&Bug Reports");
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
    }

    void MainFrame::OnMenuOpenFile(wxCommandEvent &event) {
        dlg::OpenFileDlg dlg(this);
        if (dlg.ShowModal() == wxID_CANCEL) {
            return;
        }
        dlg.UpdateLayout(&_layout);
    }

    void MainFrame::OnMenuOpenFolder(wxCommandEvent &event) {
        dlg::OpenWorkspaceDirDlg dlg(this);
        if (dlg.ShowModal() == wxID_CANCEL) {
            return;
        }
        dlg.UpdateLayout(&_layout);
    }

    void MainFrame::OnMenuSaveFile(wxCommandEvent &event) {
        EditorPane *pane = _layout.GetEditorPane();

        const wxString &path = pane->GetCurrentEditorPath();
        if (path.empty()) {
            // there is no editor currently open so we don't know what to save
            return;
        }

        if (!pane->SaveFile(path)) {
            OnMenuSaveFileAs(event);
            event.Skip();
        }
    }

    void MainFrame::OnMenuSaveFileAs(wxCommandEvent &event) {
        dlg::SaveFileAsDlg dlg(this);
        if (dlg.ShowModal() == wxID_CANCEL) {
            return;
        }
        dlg.WriteEditorContents(_layout.GetEditorPane());
    }

    void MainFrame::OnMenuCloseFolder(wxCommandEvent &event) {
        _layout.GetExplorerPane()->CloseDir();
    }

    void MainFrame::OnMenuCloseEditor(wxCommandEvent &event) {
        _layout.GetEditorPane()->CloseEditor();
    }

    void MainFrame::OnMenuAbout(wxCommandEvent &event) {
        wxAboutDialogInfo aboutInfo = ProgInfo::GenerateAboutDialogInfo();
        wxAboutBox(aboutInfo);
    }

    void MainFrame::OnMenuQuit(wxCommandEvent &event) {
        Close(true);
    }

    void MainFrame::OnMenuURLSourcePage(wxCommandEvent &event) {
        ShowURL("https://gitlab.com/kosude/texedit");
    }

    void MainFrame::OnMenuURLFeatureRequest(wxCommandEvent &event) {
        ShowURL("https://gitlab.com/kosude/texedit/issues");
    }

    void MainFrame::OnMenuURLBugReport(wxCommandEvent &event) {
        ShowURL("https://gitlab.com/kosude/texedit/issues");
    }

    void MainFrame::OnMenuURLUserManual(wxCommandEvent &event) {
        ShowURL("https://kosude.gitlab.io/texedit/");
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

        EVT_MENU(wxID_EXIT,     MainFrame::OnMenuQuit)
        EVT_MENU(wxID_ABOUT,    MainFrame::OnMenuAbout)

        EVT_MENU(Menu_OpenFile,             MainFrame::OnMenuOpenFile)
        EVT_MENU(Menu_OpenFolder,           MainFrame::OnMenuOpenFolder)
        EVT_MENU(Menu_SaveFile,             MainFrame::OnMenuSaveFile)
        EVT_MENU(Menu_SaveFileAs,           MainFrame::OnMenuSaveFileAs)
        EVT_MENU(Menu_CloseEditor,          MainFrame::OnMenuCloseEditor)
        EVT_MENU(Menu_CloseFolder,          MainFrame::OnMenuCloseFolder)
        EVT_MENU(Menu_URLSourcePage,        MainFrame::OnMenuURLSourcePage)
        EVT_MENU(Menu_URLFeatureRequest,    MainFrame::OnMenuURLFeatureRequest)
        EVT_MENU(Menu_URLBugReport,         MainFrame::OnMenuURLBugReport)
        EVT_MENU(Menu_URLUserManual,        MainFrame::OnMenuURLUserManual)
        EVT_MENU(Menu_PaneExplorer,         MainFrame::OnMenuPaneExplorer)
        EVT_MENU(Menu_PaneOutput,           MainFrame::OnMenuPaneOutput)
        EVT_MENU(Menu_PanePreview,          MainFrame::OnMenuPanePreview)
    wxEND_EVENT_TABLE()
}
