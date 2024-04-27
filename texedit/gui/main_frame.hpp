/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__root_frame_hpp__
#define __texedit__root_frame_hpp__

#include <wx/wx.h>

#include "process/process_mgr.hpp"
#include "process/services/compiler_process.hpp"
#include "process/services/pdf_server_process.hpp"
#include "util/logger.hpp"
#include "preview_panel.hpp"

namespace te::gui {
    class MainFrame : public wxFrame {
    public:
        MainFrame();
        ~MainFrame();

    private:
        util::GlobalLogger *_logger;
        wxListBox *_lb;

        PreviewPanel *_preview;

        proc::ProcessManager _proc_mgr;
        proc::CompilerProcess *_compiler_proc;
        proc::PDFServerProcess *_preview_proc;

        void BuildSplitLayout();
        void BuildMenuBar();

        void OnIdle(wxIdleEvent &ev);

        void ShowURL(const wxString &url);

        void OnMenuAbout(wxCommandEvent &event);
        void OnMenuQuit(wxCommandEvent &event);
        void OnMenuURLSourcePage(wxCommandEvent &event);
        void OnMenuURLFeatureRequest(wxCommandEvent &event);
        void OnMenuURLBugReport(wxCommandEvent &event);
        void OnMenuURLUserManual(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif
