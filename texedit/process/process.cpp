/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "process.hpp"

#include "process_mgr.hpp"

#include <wx/log.h>
#include <wx/txtstrm.h>

namespace te::proc {
    Process::Process(ProcessManager *mgr, const std::vector<const char*> &argv) : wxProcess(mgr->GetCmdParent()), _mgr{mgr} {
        Redirect();

        wxExecute(argv.data(), wxEXEC_ASYNC, this);
        wxLogMessage("Executing (pid %li): %s", GetPid(), ArgvToCmdStr(argv));
    }

    void Process::OnTerminate(int pid, int status) {
        _mgr->HandleProcessTerminated(this, pid, status);
    }

    wxString Process::ReadLineStdout() {
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

    wxString Process::ArgvToCmdStr(const std::vector<const char *> &argv) {
        wxString s;
        for (const char *a : argv) {
          s << a << " ";
        }
        return s;
    }
}
