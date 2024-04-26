/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_server_process_hpp__
#define __texedit__pdf_server_process_hpp__

#include <wx/wx.h>

#include "process/process.hpp"

namespace te::proc {
    class PDFServerProcess : public Process {
    public:
        PDFServerProcess(ProcessManager *mgr);

    private:
        wxString _cmd;

        std::vector<const char *> GetArgv();
    };
}

#endif
