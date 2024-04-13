/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__app_hpp__
#define __texedit__app_hpp__

#include <wx/wx.h>

namespace te {
    class App : public wxApp {
    public:
        bool OnInit() override;
    };
}

#endif
