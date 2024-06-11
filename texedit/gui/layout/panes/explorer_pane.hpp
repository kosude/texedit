/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__explorer_pane_hpp__
#define __texedit__explorer_pane_hpp__

#include "pane_base.hpp"
#include "editor_pane.hpp"

#include <wx/wx.h>
#include <wx/dirctrl.h>

namespace te::gui {
    class LayoutManager;

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
        ExplorerPane(wxWindow *parent, EditorPane *editor_pane, LayoutManager *parent_layout);

        inline LocalDirCtrl *GetDirCtrl() const { return _dirctrl; }

        void ChangeRootDir(const wxString &path);
        void CloseDir();

    private:
        wxSizerItem *_empty_tree_stretch_spacer[2];
        wxButton *_empty_tree_btn;
        void AddEmptyTreeButton();

        wxBoxSizer *_sizer;
        LocalDirCtrl *_dirctrl{nullptr};

        LayoutManager *_parent_layout;
        EditorPane *_rel_editor;

        void OnButtonOpenFolder(wxCommandEvent &event);
        void OnTreeFileActivated(wxTreeEvent &event);

        wxDECLARE_EVENT_TABLE();
    };
}

#endif
