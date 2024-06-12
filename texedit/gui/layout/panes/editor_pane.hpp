/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#include <vector>
#ifndef __texedit__editor_pane_hpp__
#define __texedit__editor_pane_hpp__

#include "pane_base.hpp"
#include "gui/editor/src_editor_component.hpp"

#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/aui/auibook.h>

namespace te::gui {
    class EditorPane : public PaneBase {
    public:
        EditorPane(wxWindow *parent, const wxString &path = "");

        void OpenEditor(const wxString &path = "", int index = -1);
        void CloseEditor(int index = -1);

        bool SaveFile(const wxString &path, int editor_index = -1);

        wxString GetCurrentEditorPath();

    private:
        wxBoxSizer *_sizer;
        wxAuiNotebook *_notebook;
    };
}

#endif
