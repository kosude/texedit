/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "logger.hpp"

namespace te::util {
    GlobalLogger::GlobalLogger(wxListBox *lb) : wxLogStderr(stderr), _lbox{lb} {
    }

    void GlobalLogger::DoLogTextAtLevel(wxLogLevel level, const wxString &msg) {
        switch (level) {
            case wxLOG_Debug:
            case wxLOG_Trace:
                wxMessageOutputDebug().Output(msg + "\n");
                return;
            default:
                AppendOutput(msg);
                return;
        }
    }

    void GlobalLogger::AppendOutput(const wxString &msg) {
        DoLogText(msg);

        _lbox->Append(msg);
        _lbox->EnsureVisible(_lbox->GetCount() - 1);
    }
}
