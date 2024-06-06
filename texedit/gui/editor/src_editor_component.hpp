/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __devinit__src_editor_component_hpp__
#define __devinit__src_editor_component_hpp__

#include <wx/stc/stc.h>

namespace te::gui::editor {
    class SrcEditor : public wxStyledTextCtrl {
    public:
        SrcEditor(wxWindow *parent);
        ~SrcEditor();

    private:
    };
}

#endif
