/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "explorer_pane.hpp"

#include "gui/command_ids.hpp"

namespace te::gui {
    LocalDirCtrl::LocalDirCtrl(wxWindow *parent, const wxString &root, wxWindowID id) : _root{root} {
        Init();
        Create(parent, id);
    }

    void LocalDirCtrl::SetupSections() {
        AddSection(_root, wxFileNameFromPath(_root), wxFileIconsTable::folder_open);

        ExpandPath(_root);
    }

    ExplorerPane::ExplorerPane(wxWindow *parent) : PaneBase(parent) {
        _sizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(_sizer);

        AddEmptyTreeButton();
    }

    void ExplorerPane::ChangeRootDir(const wxString &path) {
        _sizer->Clear();

        // destroy and recreate the dirctrl
        if (_dirctrl) {
            _sizer->Detach(_dirctrl);
            _dirctrl->Destroy();
        }
        _dirctrl = new LocalDirCtrl(this, path, wxID_ANY);
        _sizer->Add(_dirctrl, 1, wxEXPAND);
    }

    void ExplorerPane::AddEmptyTreeButton() {
        _sizer->Clear();

        _empty_tree_btn = new wxButton(this, cmds::Button_OpenFolder, "Open a folder");
        _empty_tree_stretch_spacer[0] = _sizer->AddStretchSpacer();
        _sizer->Add(_empty_tree_btn, 0, wxALIGN_CENTER);
        _empty_tree_stretch_spacer[1] = _sizer->AddStretchSpacer();
    }
}
