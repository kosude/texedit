/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main.hpp"

#include "gui/main_frame.hpp"
#include "util/log.hpp"

wxIMPLEMENT_APP(te::Application);

namespace te {
    bool Application::OnExceptionInMainLoop() {
        try {
            throw;
        } catch (const std::exception &e) {
            util::log::Fatal(e.what());

            if (wxMessageBox("An unexpected exception has occurred:\n"
                             "\"" + std::string{e.what()} + "\"\n\n"
                             "TexEdit can attempt to keep running so you can save your data. Do you want to try?",
                             "Fatal Error", wxYES | wxNO | wxICON_ERROR)
                    == wxYES) {
                util::log::Warn("Attempting to continue execution following a potentially fatal exception");
                return true;
            }
        }

        return false;
    }

    void Application::OnUnhandledException() {
        wxMessageBox("An unhandled exception has occurred and TexEdit cannot recover.\n"
                     "The program will now terminate.",
                     "Unhandled Exception", wxOK | wxICON_ERROR);
    }

    bool Application::OnInit() {
        util::log::ResetLogColour();

        // TODO: command-line parsing here

        // show root (editor) window
        MainFrame *main_frame = new MainFrame();
        SetTopWindow(main_frame);
        main_frame->Show();

        return true;
    }
}
