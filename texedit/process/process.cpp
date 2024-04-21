/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "process.hpp"

#include "process_mgr.hpp"

#include <wx/txtstrm.h>
#include <iostream>

namespace te {
    Process::Process(wxEvtHandler *parent, ProcessManager *mgr) : wxProcess(parent), _mgr{mgr} {
    }

    void Process::OnTerminate(int pid, int status) {
        _mgr->HandleProcessTerminated(this, pid, status);
    }

    PipedProcess::PipedProcess(wxEvtHandler *parent, ProcessManager *mgr) : Process(parent, mgr) {
        Redirect();
    }

    wxString PipedProcess::ReadLineStdout() {
        wxString r{""};

        if (IsInputAvailable()) {
            wxTextInputStream tis(*GetInputStream());
            r << tis.ReadLine();
        }
        if (IsErrorAvailable()) {
            wxTextInputStream tis(*GetErrorStream());
            r << tis.ReadLine();
        }

        return r;
    }

    void PipedProcess::OnTerminate(int pid, int status) {
        _mgr->HandlePipedProcessTerminated(this, pid, status);
    }
}
