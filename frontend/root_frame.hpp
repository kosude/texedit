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
    class RootFrame : public wxFrame {
    public:
        RootFrame();

    private:
        // menu bar shenanigans
        class MenuBar {
        public:
            wxMenuBar *component;

            MenuBar(
                RootFrame *frame
            );

        private:
            enum {
                _ID_OPEN_REPOSITORY = 1,
            };

            RootFrame *_frame;

            void _OnFileExit();
            void _OnHelpGitRepository();
        };

        MenuBar _menuBar;
    };
}

#endif
