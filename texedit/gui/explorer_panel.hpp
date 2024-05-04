/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__explorer_panel_hpp__
#define __texedit__explorer_panel_hpp__

#include <wx/wx.h>
#include <wx/dirctrl.h>

namespace te::gui {
    class ExplorerPanel : public wxPanel {
    public:
        ExplorerPanel(wxWindow *parent);

    private:
        wxBoxSizer *_sizer;
        wxGenericDirCtrl *_dirctl;
    };
}

#endif
