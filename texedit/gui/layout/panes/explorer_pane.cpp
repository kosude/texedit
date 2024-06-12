/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "explorer_pane.hpp"

#include "gui/common/dialogues.hpp"

enum {
    Button_OpenFolder = wxID_HIGHEST + 1,
    DirCtrl_Main,
};

namespace te::gui {
    LocalDirCtrl::LocalDirCtrl(wxWindow *parent, const wxString &root, wxWindowID id) : _root{root} {
        Init();
        Create(parent, id);
    }

    void LocalDirCtrl::SetupSections() {
        AddSection(_root, wxFileNameFromPath(_root), wxFileIconsTable::folder_open);

        ExpandPath(_root);
    }

    ExplorerPane::ExplorerPane(wxWindow *parent, EditorPane *editor_pane, LayoutManager *parent_layout)
        : PaneBase(parent),
          _rel_editor{editor_pane},
          _parent_layout{parent_layout}
    {
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
        _dirctrl = new LocalDirCtrl(this, path, DirCtrl_Main);
        _sizer->Add(_dirctrl, 1, wxEXPAND);
    }

    void ExplorerPane::CloseDir() {
        if (!_dirctrl) {
            return;
        }

        _sizer->Detach(_dirctrl);
        _dirctrl->Destroy();
        _dirctrl = nullptr;
    }

    void ExplorerPane::AddEmptyTreeButton() {
        _sizer->Clear();

        _empty_tree_btn = new wxButton(this, Button_OpenFolder, "Open a folder");
        _empty_tree_stretch_spacer[0] = _sizer->AddStretchSpacer();
        _sizer->Add(_empty_tree_btn, 0, wxALIGN_CENTER);
        _empty_tree_stretch_spacer[1] = _sizer->AddStretchSpacer();
    }

    void ExplorerPane::OnButtonOpenFolder(wxCommandEvent &event) {
        dlg::OpenWorkspaceDirDlg dlg(this);
        if (dlg.ShowModal() == wxID_CANCEL) {
            return;
        }
        dlg.UpdateLayout(_parent_layout);
    }

    void ExplorerPane::OnTreeFileActivated(wxTreeEvent &event) {
        if (!_dirctrl) {
            event.Skip();
            return;
        }

        _rel_editor->OpenEditor(_dirctrl->GetPath(event.GetItem()));
    }

    wxBEGIN_EVENT_TABLE(ExplorerPane, PaneBase)
        EVT_BUTTON(Button_OpenFolder, ExplorerPane::OnButtonOpenFolder)
        EVT_DIRCTRL_FILEACTIVATED(DirCtrl_Main, ExplorerPane::OnTreeFileActivated)
    wxEND_EVENT_TABLE()
}
