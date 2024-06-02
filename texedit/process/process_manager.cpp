/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "process_manager.hpp"

// These headers are used indirectly by the ExecuteAsync template, as we need to know they inherit from the Process class to
// not alert the static_assert. IWYU pragmas are respected by clangd and avoid 'unused include' warnings.
#include "services/compiler_process.hpp"    // IWYU pragma: keep

#include <wx/log.h>
#include <type_traits>

namespace te::proc {
    template CompilerProcess *ProcessManager::ExecuteAsync<CompilerProcess>();

    ProcessManager::ProcessManager(wxEvtHandler *cmd_parent) : _cmd_parent{cmd_parent} {
    }

    ProcessManager::~ProcessManager() {
        for (auto p : _running) {
            wxProcess::Kill(p->GetPid(), wxSIGINT);
        }
    }

    template <typename P>
    P *ProcessManager::ExecuteAsync() {
        static_assert(std::is_base_of<Process, P>::value, "In ProcessManager::ExecuteAsync(), type parameter P must derive from the Process class");

        P *proc = new P(this);
        proc->Start();
        _running.push_back(proc);

        return proc;
    }

    wxString ProcessManager::PollAsyncOutput() {
        wxString r{""};
        for (auto p : _running) {
            r << p->ReadLineStdout();
        }
        return r;
    }

    void ProcessManager::HandleProcessTerminated(Process *p, int pid, int status) {
        wxLogMessage("Process %d terminated with code %d", pid, status);
        RemoveProcess(p);
    }

    void ProcessManager::RemoveProcess(Process *p) {
        _running.erase(std::remove(_running.begin(), _running.end(), p));
    }
}
