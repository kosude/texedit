/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__dialogues_hpp__
#define __texedit__dialogues_hpp__

#include <wx/filedlg.h>
#include <wx/dirdlg.h>

namespace te::gui {
    class LayoutManager;
}

namespace te::gui::dlg {
    class OpenFileDlg : public wxFileDialog {
    public:
        OpenFileDlg(wxWindow *parent);

        void UpdateLayout(LayoutManager *layout);
    };

    class OpenWorkspaceDirDlg : public wxDirDialog {
    public:
        OpenWorkspaceDirDlg(wxWindow *parent);

        void UpdateLayout(LayoutManager *layout);
    };
}

#endif
