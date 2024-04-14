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
    class Application : public wxApp {
    public:
        bool OnExceptionInMainLoop() override;
        void OnUnhandledException() override;

        bool OnInit() override;
        int OnExit() override;
    };
}

wxDECLARE_APP(te::Application);

#endif
