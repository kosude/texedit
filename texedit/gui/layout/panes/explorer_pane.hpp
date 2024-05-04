/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__explorer_pane_hpp__
#define __texedit__explorer_pane_hpp__

#include <wx/wx.h>
#include <wx/dirctrl.h>
#include "pane_base.hpp"

namespace te::gui {
    class ExplorerPane : public PaneBase {
    public:
        ExplorerPane(wxWindow *parent);

    private:
        wxBoxSizer *_sizer;
        wxGenericDirCtrl *_dirctl;
    };
}

#endif
