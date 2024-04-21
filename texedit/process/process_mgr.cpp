/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "process_mgr.hpp"

#include <wx/log.h>

namespace te {
    ProcessManager::ProcessManager(wxEvtHandler *cmd_parent) : _cmd_parent{cmd_parent} {
    }

    ProcessManager::~ProcessManager() {
        // stop and delete all processes if they are still running when the process manager is destroyed
        for (auto p : _all_async) {
            delete p.second;
        }
    }

    void ProcessManager::ExecuteAsync(int id, const char *const *argv) {
        Process *proc = new Process(_cmd_parent, this);
        proc->SetCmd(argv[0]);

        // make a string with the given arguments so it can be logged
        wxString cmdstr;
        for (int i = 0; argv[i] != 0; i++)
            cmdstr << argv[i] << " ";
        wxLogMessage("Executing command: %s", cmdstr);

        wxExecute(argv, wxEXEC_ASYNC, proc);

        _all_async.emplace(id, proc);
    }

    void ProcessManager::ExecutePipedAsync(int id, const char *const *argv) {
        PipedProcess *piproc = new PipedProcess(_cmd_parent, this);
        piproc->SetCmd(argv[0]);

        // make a string with the given arguments so it can be logged
        wxString cmdstr;
        for (int i = 0; argv[i] != 0; i++)
            cmdstr << argv[i] << " ";
        wxLogMessage("Executing command: %s", cmdstr);

        wxExecute(argv, wxEXEC_ASYNC, piproc);

        _piped_running.emplace(id, piproc);
        _all_async.emplace(id, piproc);
    }

    wxString ProcessManager::PollPipedOutput(int id) {
        wxString r{""};

        // merge all output if no id was specified
        if (id == wxINT32_MAX) {
            for (auto p : _piped_running) {
                r << p.second->ReadLineStdout();
            }

            return r;
        }

        // otherwise just get output of process with given id
        if (_piped_running.find(id) != _piped_running.end()) {
            r << _piped_running.at(id)->ReadLineStdout();
        }

        return r;
    }

    void ProcessManager::HandleProcessTerminated(Process *p, int pid, int status) {
        wxLogMessage("Process %d (%s) terminated with code %d",
                     pid, p->GetCmd(), status);

        RemoveProcess(p);
    }

    void ProcessManager::HandlePipedProcessTerminated(PipedProcess *p, int pid, int status) {
        wxLogMessage("Process %d (%s) terminated with code %d",
                     pid, p->GetCmd(), status);

        RemovePipedProcess(p);
    }

    void ProcessManager::RemoveProcess(Process *p) {
        auto it = _all_async.begin();
        while (it != _all_async.end()) {
            if (it->second == p) {
                it = _all_async.erase(it);
            } else {
                it++;
            }
        }
    }

    void ProcessManager::RemovePipedProcess(PipedProcess *p) {
        auto it = _piped_running.begin();
        while (it != _piped_running.end()) {
            if (it->second == p) {
                it = _piped_running.erase(it);
            } else {
                it++;
            }
        }

        RemoveProcess(p);
    }
}
