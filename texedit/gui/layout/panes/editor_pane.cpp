/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "editor_pane.hpp"
#include "gui/editor/src_editor_component.hpp"

namespace te::gui {
    EditorPane::EditorPane(wxWindow *parent, const wxString &path) : PaneBase{parent}, _path{path} {
        _src_editor = new editor::SrcEditor(this);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_src_editor, 1, wxEXPAND);
        SetSizer(_sizer);

        HideEditor();
    }

    void EditorPane::LoadFile(const wxString &path) {
        if (!_src_editor->IsShown()) {
            ShowEditor();
        }

        _src_editor->LoadFile(path);
        _path = path;
    }

    bool EditorPane::SaveFile(const wxString &path) {
        return _src_editor->SaveFile(path);
    }

    void EditorPane::HideEditor() {
        if (!_src_editor->IsShown()) {
            return;
        }

        _path = "";
        _sizer->Hide(_src_editor);
        _sizer->Layout();
    }

    void EditorPane::ShowEditor() {
        if (_src_editor->IsShown()) {
            return;
        }

        _sizer->Show(_src_editor);
        _sizer->Layout();
    }
}
