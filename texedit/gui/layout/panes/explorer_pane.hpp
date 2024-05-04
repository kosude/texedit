/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__explorer_pane_hpp__
#define __texedit__explorer_pane_hpp__

#include <wx/wx.h>
#include <wx/dirctrl.h>
#include "pane_base.hpp"

namespace te::gui {
    // An implementation of wxGenericDirCtrl that is local to a specified directory, as opposed to listing the entire filesystem
    class LocalDirCtrl : public wxGenericDirCtrl {
    public:
        LocalDirCtrl(wxWindow *parent, const wxString &root, wxWindowID id = wxID_ANY);

        void SetupSections() override;

    private:
        wxString _root;
    };

    class ExplorerPane : public PaneBase {
    public:
        ExplorerPane(wxWindow *parent);

        inline LocalDirCtrl *GetDirCtrl() const { return _dirctrl; }

        void ChangeRootDir(const wxString &path);

    private:
        wxSizerItem *_empty_tree_stretch_spacer[2];
        wxButton *_empty_tree_btn;
        void AddEmptyTreeButton();

        wxBoxSizer *_sizer;
        LocalDirCtrl *_dirctrl{nullptr};
    };
}

#endif
