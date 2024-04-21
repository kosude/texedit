/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__process_mgr_hpp__
#define __texedit__process_mgr_hpp__

#include <wx/process.h>

#include <vector>

namespace te::proc {
    class ProcessManager;

    class Process : public wxProcess {
    public:
        Process(wxEvtHandler *parent, ProcessManager *mgr);

        virtual void OnTerminate(int pid, int status) override;

        inline void SetCmd(const wxString &cmd) { _cmd = cmd; }
        inline wxString GetCmd() const { return _cmd; }

    protected:
        ProcessManager *_mgr;
        wxString _cmd{};
    };

    class PipedProcess : public Process {
    public:
        PipedProcess(wxEvtHandler *parent, ProcessManager *mgr);

        wxString ReadLineStdout();

        virtual void OnTerminate(int pid, int status) override;
    };
}

#endif
