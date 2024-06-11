/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "dialogues.hpp"

#include "gui/layout/layout_manager.hpp"
#include "gui/layout/panes/explorer_pane.hpp"

namespace te::gui::dlg {
    OpenFileDlg::OpenFileDlg(wxWindow *parent)
        : wxFileDialog(
            parent,
            "Open file",
            wxEmptyString,
            wxEmptyString,
            wxFileSelectorDefaultWildcardStr,
            wxFD_DEFAULT_STYLE | wxFD_OPEN | wxFD_FILE_MUST_EXIST
    ) {
    }

    void OpenFileDlg::UpdateLayout(LayoutManager *layout) {
        layout->GetEditorPane()->LoadFile(GetPath());
    }

    OpenWorkspaceDirDlg::OpenWorkspaceDirDlg(wxWindow *parent)
        : wxDirDialog(
            parent,
            "Open directory",
            wxEmptyString,
            wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST
    ) {
    }

    void OpenWorkspaceDirDlg::UpdateLayout(LayoutManager *layout) {
        layout->GetExplorerPane()->ChangeRootDir(GetPath());

        layout->Update();
    }
}
