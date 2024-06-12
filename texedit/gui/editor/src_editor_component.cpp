/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "src_editor_component.hpp"

namespace te::gui::editor {
    SrcEditor::SrcEditor(wxWindow *parent, const wxString &path) : wxStyledTextCtrl(parent), _path{path} {
        // TODO: set colours depending on dark or light theme
        // TODO: note that the theme might be system dependent, as on macOS, so properly managing themes with some sort of manager class would be best
        SetMarginType(1, wxSTC_MARGIN_NUMBER);
        SetMarginMask(1, 0);
        SetMarginWidth(1, 20);

        if (!path.empty()) {
            LoadFile(path);
        }

        // TODO lexers for styling and syntax highlighting.
    }

    SrcEditor::~SrcEditor() {
    }
}
