/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "editor_pane.hpp"
#include "gui/editor/src_editor_component.hpp"

#include <wx/filename.h>

namespace te::gui {
    EditorPane::EditorPane(wxWindow *parent, const wxString &path) : PaneBase{parent} {
        _notebook = new wxAuiNotebook(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_CLOSE_ON_ACTIVE_TAB | wxAUI_NB_MIDDLE_CLICK_CLOSE
                | wxAUI_NB_TOP
        );

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_notebook, 1, wxEXPAND);
        SetSizer(_sizer);
    }

    bool EditorPane::SaveFile(const wxString &path, int editor_index) {
        editor::SrcEditor *editor = (editor_index > -1)
            ? (editor::SrcEditor *) _notebook->GetPage(editor_index)
            : (editor::SrcEditor *) _notebook->GetCurrentPage();
        if (!editor) {
            return false;
        }

        return editor->SaveFile(path);
    }

    void EditorPane::OpenEditor(const wxString &path, int index) {
        editor::SrcEditor *editor = new editor::SrcEditor(_notebook, path);

        wxString caption = wxFileNameFromPath(path);

        if (index > -1) {
            _notebook->InsertPage(index, editor, caption);
        } else {
            _notebook->AddPage(editor, caption);
        }
    }

    void EditorPane::CloseEditor(int index) {
        int i = (index > -1)
            ? index
            : _notebook->GetPageIndex(_notebook->GetCurrentPage());

        _notebook->DeletePage(i);
    }

    wxString EditorPane::GetCurrentEditorPath() {
        editor::SrcEditor *editor = (editor::SrcEditor *) _notebook->GetCurrentPage();
        if (!editor) {
            return "";
        }

        return editor->GetPath();
    }
}
