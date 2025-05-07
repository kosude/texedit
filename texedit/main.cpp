/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "main.hpp"

#include "gui/main_frame.hpp"
#include "pdf_render/poppler_log.hpp"

wxIMPLEMENT_APP(te::Application);

namespace te {
bool Application::OnExceptionInMainLoop() {
  wxString what;
  try {
    throw;
  } catch (const std::exception *e) {
    what = e->what();
  } catch (...) {
    what = "Unknown runtime error";
  }

  wxLogError("(FATAL): %s", what);

  if (wxMessageBox("An unexpected exception has occurred:\n"
                   "\"" +
                       what +
                       "\"\n\n"
                       "TexEdit can attempt to keep running so you can save "
                       "your data. Do you want to try?",
                   "Fatal Error", wxYES | wxNO | wxICON_ERROR) == wxYES) {
    wxLogWarning("Attempting to continue execution following a potentially "
                 "fatal exception");
    return true;
  }

  return false;
}

void Application::OnUnhandledException() {
  wxString what;
  try {
    throw;
  } catch (const std::exception *e) {
    what = e->what();
  } catch (...) {
    what = "Unknown runtime error";
  }

  wxLogError("(FATAL): %s", what);

  wxMessageBox("An unexpected exception has occurred:\n"
               "\"" +
                   what +
                   "\"\n\n"
                   "This was unhandled and TexEdit cannot recover. The program "
                   "will now terminate.",
               "Unhandled Exception", wxOK | wxICON_ERROR);
}

bool Application::OnInit() {
  // TODO: command-line parsing here

  // initialise logging for PDF document processing
  pdfr::CaptureRuntimeLogging();

  // show root (editor) window
  gui::MainFrame *main_frame = new gui::MainFrame();
  SetTopWindow(main_frame);
  main_frame->Show();

  return true;
}

int Application::OnExit() {
  wxLogStatus("Exiting...");
  return 0;
}
} // namespace te
