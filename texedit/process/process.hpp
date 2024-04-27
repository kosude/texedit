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
        Process(ProcessManager *mgr);

        virtual void Start();
        wxString ReadLineStdout();

        virtual void OnTerminate(int pid, int status) override;

    protected:
        void StartHelper(const std::vector<const char*> &argv);

        // In these functions, true is returned if the read line should be passed through as usual, and false if it should be consumed.
        virtual bool OnStdoutInputAvailable(const wxString &line);
        virtual bool OnStdoutErrorAvailable(const wxString &line);

    private:
        ProcessManager *_mgr;

        wxString ArgvToCmdStr(const std::vector<const char *> &argv);
    };
}

#endif
