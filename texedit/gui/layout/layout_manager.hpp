/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__layout_manager_hpp__
#define __texedit__layout_manager_hpp__

#include <wx/aui/aui.h>

namespace te::gui {
    class EditorPane;
    class ExplorerPane;
    class OutputPane;
    class PreviewPane;

    class LayoutManager : public wxAuiManager {
    public:
        LayoutManager(wxWindow *win);
        ~LayoutManager();

        inline EditorPane   *GetEditorPane()   const { return _editor; }
        inline ExplorerPane *GetExplorerPane() const { return _explorer; }
        inline OutputPane   *GetOutputPane()   const { return _output; }
        inline PreviewPane  *GetPreviewPane()  const { return _preview; }

    private:
        wxWindow *_win;

        EditorPane *_editor;
        ExplorerPane *_explorer;
        OutputPane *_output;
        PreviewPane *_preview;
    };
}

#endif
