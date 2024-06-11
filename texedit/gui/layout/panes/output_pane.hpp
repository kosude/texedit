/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__output_pane_hpp__
#define __texedit__output_pane_hpp__

#include "pane_base.hpp"

#include <wx/sizer.h>
#include <wx/listbox.h>

namespace te::gui {
    class OutputPane : public PaneBase {
    public:
        OutputPane(wxWindow *parent);

        inline wxListBox *GetListBox() const { return _listbox; }

    private:
        wxBoxSizer *_sizer;
        wxListBox *_listbox;
    };
}

#endif
