/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_server_hpp__
#define __texedit__pdf_server_hpp__

#include "process.hpp"

#include <unordered_map>

namespace te::proc {
    class ProcessManager {
    public:
        ProcessManager(wxEvtHandler *cmd_parent);
        ~ProcessManager();

        void ExecuteAsync(int id, const char *const *argv);
        void ExecutePipedAsync(int id, const char *const *argv);

        wxString PollPipedOutput(int id = wxINT32_MAX);

        void HandleProcessTerminated(Process *p, int pid, int status);
        void HandlePipedProcessTerminated(PipedProcess *p, int pid, int status);

    private:
        wxEvtHandler *_cmd_parent;

        std::unordered_map<int, Process *> _all_async{};
        std::unordered_map<int, PipedProcess *> _piped_running{};

        void RemoveProcess(Process *p);
        void RemovePipedProcess(PipedProcess *p);
    };
}

#endif
