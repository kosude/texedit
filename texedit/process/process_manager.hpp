/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__process_manager_hpp__
#define __texedit__process_manager_hpp__

#include "process.hpp"

#include <vector>

namespace te::proc {
    class ProcessManager {
    public:
        ProcessManager(wxEvtHandler *cmd_parent);
        ~ProcessManager();

        template <typename P>
        P *ExecuteAsync();

        // get output from async process stdout/stderr
        wxString PollAsyncOutput();

        void HandleProcessTerminated(Process *p, int pid, int status);

        inline wxEvtHandler *GetCmdParent() const { return _cmd_parent; }

    private:
        wxEvtHandler *_cmd_parent;

        std::vector<Process *> _running{};

        void RemoveProcess(Process *p);
    };
}

#endif
