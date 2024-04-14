/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__root_frame_hpp__
#define __texedit__root_frame_hpp__

#include <wx/wx.h>

namespace te {
    class MainFrame : public wxFrame {
    public:
        MainFrame();

    private:
        // menu bar shenanigans
        class MenuBar {
        public:
            wxMenuBar *component;

            MenuBar(
                MainFrame *frame
            );

        private:
            enum {
                _ID_OPEN_REPOSITORY = 1,
            };

            MainFrame *_frame;

            void _OnFileExit();
            void _OnHelpGitRepository();
        };

        MenuBar _menuBar;
    };
}

#endif
