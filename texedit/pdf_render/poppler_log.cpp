/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "poppler_log.hpp"

#include <wx/string.h>
#include <wx/log.h>
#include <poppler-global.h>

namespace te::pdfr {
    static void PopplerDebugFunc(const std::string &msg, void *closure) {
        wxLogError("poppler: " + wxString{msg});
    }

    void CaptureRuntimeLogging() {
        poppler::set_debug_error_function(PopplerDebugFunc, nullptr);
    }
}
