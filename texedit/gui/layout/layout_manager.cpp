/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "layout_manager.hpp"

#include "panes/editor_pane.hpp"
#include "panes/explorer_pane.hpp"
#include "panes/output_pane.hpp"
#include "panes/preview_pane.hpp"

#include <wx/textctrl.h>

namespace te::gui {
    LayoutManager::LayoutManager(wxWindow *win) : wxAuiManager(win), _win{win} {
        _editor   = new EditorPane(_win);
        _explorer = new ExplorerPane(_win, _editor, this);
        _output   = new OutputPane(_win);
        _preview  = new PreviewPane(_win);

        AddPane(_editor, wxAuiPaneInfo()
            .Name       (_editor_id)
            .Caption    ("Editor")
            .Direction  (wxAUI_DOCK_CENTER)
            .CloseButton(false)
            .MinSize    (400, 400)
            .BestSize   (700, 400));

        AddPane(_explorer, wxAuiPaneInfo()
            .Name     (_explorer_id)
            .Caption  ("Explorer")
            .Direction(wxAUI_DOCK_LEFT)
            .MinSize  (100, 200)
            .BestSize (200, 400));

        AddPane(_preview, wxAuiPaneInfo()
            .Name     (_preview_id)
            .Caption  ("PDF Preview")
            .Direction(wxAUI_DOCK_RIGHT)
            .MinSize  (100, 200)
            .BestSize (400, 700));

        AddPane(_output, wxAuiPaneInfo()
            .Name     (_output_id)
            .Caption  ("Output")
            .Direction(wxAUI_DOCK_RIGHT)
            .Position (1)
            .MinSize  (100, 200)
            .BestSize (400, 200));

        Update();
    }

    LayoutManager::~LayoutManager() {
        UnInit();
    }

    void LayoutManager::ShowEditorPane() {
        _ShowPane(_editor_id);
    }
    void LayoutManager::ShowExplorerPane() {
        _ShowPane(_explorer_id);
    }
    void LayoutManager::ShowOutputPane() {
        _ShowPane(_output_id);
    }
    void LayoutManager::ShowPreviewPane() {
        _ShowPane(_preview_id);
    }

    void LayoutManager::_ShowPane(const char *id) {
        wxAuiPaneInfo &p = GetPane(id);
        p.Show();
        Update();
    }
}
