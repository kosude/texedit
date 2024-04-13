/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "app.hpp"

#include "root_frame.hpp"

wxIMPLEMENT_APP(te::App);

namespace te {
    bool App::OnInit() {
        // show root (editor) window
        RootFrame *root = new RootFrame();
        root->Show();
        return true;
    }
}
