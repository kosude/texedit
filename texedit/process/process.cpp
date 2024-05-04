/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "process.hpp"

#include "process_manager.hpp"

#include <wx/log.h>
#include <wx/txtstrm.h>

namespace te::proc {
    Process::Process(ProcessManager *mgr) : wxProcess(mgr->GetCmdParent()), _mgr{mgr} {
        Redirect();
    }

    void Process::Start() {
        StartHelper({});
    }

    wxString Process::ReadLineStdout() {
        wxString r{""};

        if (IsInputAvailable()) {
            wxTextInputStream tis(*GetInputStream());
            wxString l = tis.ReadLine();

            if (OnStdoutInputAvailable(l)) {
                r << l;
            }
        }
        if (IsErrorAvailable()) {
            wxTextInputStream tis(*GetErrorStream());
            wxString l = tis.ReadLine();

            if (OnStdoutErrorAvailable(l)) {
                r << l;
            }
        }

        return r;
    }

    void Process::OnTerminate(int pid, int status) {
        _mgr->HandleProcessTerminated(this, pid, status);
    }

    void Process::StartHelper(const std::vector<const char*> &argv) {
        wxExecute(argv.data(), wxEXEC_ASYNC, this);
        wxLogMessage("Executing (pid %li): %s", GetPid(), ArgvToCmdStr(argv));
    }

    bool Process::OnStdoutInputAvailable(const wxString &line) {
        return true;
    }

    bool Process::OnStdoutErrorAvailable(const wxString &line) {
        return true;
    }

    wxString Process::ArgvToCmdStr(const std::vector<const char *> &argv) {
        wxString s;
        for (const char *a : argv) {
          s << a << " ";
        }
        return s;
    }
}
