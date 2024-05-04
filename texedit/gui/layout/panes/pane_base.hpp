/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pane_base_hpp__
#define __texedit__pane_base_hpp__

#include <wx/gdicmn.h>
#include <wx/panel.h>

namespace te::gui {
    class PaneBase : public wxPanel {
    public:
        using wxPanel::wxPanel;
    };
}

#endif
