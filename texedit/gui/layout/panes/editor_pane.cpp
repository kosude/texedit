/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "editor_pane.hpp"
#include "gui/editor/src_editor_component.hpp"

namespace te::gui {
    EditorPane::EditorPane(wxWindow *parent) : PaneBase{parent}, _path{""} {
        _src_editor = new editor::SrcEditor(this);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_src_editor, 1, wxEXPAND);
        SetSizer(_sizer);
    }

    void EditorPane::LoadFile(const wxString &path) {
        _src_editor->LoadFile(path);
        _path = path;
    }

    bool EditorPane::SaveFile(const wxString &path) {
        return _src_editor->SaveFile(path);
    }
}
