/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__process_hpp__
#define __texedit__process_hpp__

#include <wx/process.h>
#include <vector>

namespace te::proc {
    class ProcessManager;

    class Process : public wxProcess {
    public:
        Process(ProcessManager *mgr, const std::vector<const char*> &argv);

        wxString ReadLineStdout();

        void OnTerminate(int pid, int status) override;

    private:
        ProcessManager *_mgr;

        wxString ArgvToCmdStr(const std::vector<const char *> &argv);
    };
}

#endif
