/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__editor_pane_hpp__
#define __texedit__editor_pane_hpp__

#include "pane_base.hpp"
#include "gui/editor/src_editor_component.hpp"

#include <wx/wx.h>
#include <wx/stc/stc.h>

namespace te::gui {
    class EditorPane : public PaneBase {
    public:
        EditorPane(wxWindow *parent);

        void LoadFile(const wxString &path);

    private:
        wxBoxSizer *_sizer;

        editor::SrcEditor *_src_editor;
    };
}

#endif
