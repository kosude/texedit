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

namespace te {
    class MainFrame : public wxFrame {
    public:
        MainFrame();

    private:
        void BuildSplitLayout();
        void BuildMenuBar();

        void ShowURL(const std::string &url);

        void OnMenuQuit(wxCommandEvent &event);
        void OnMenuURLSourcePage(wxCommandEvent &event);
        void OnMenuURLFeatureRequest(wxCommandEvent &event);
        void OnMenuURLBugReport(wxCommandEvent &event);
        void OnMenuURLUserManual(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif
