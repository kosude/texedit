/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_server_process_hpp__
#define __texedit__pdf_server_process_hpp__

#include <wx/wx.h>

#include "process/process.hpp"

namespace te::proc {
    class PDFServerProcess : public Process {
    public:
        using OnPortFoundCallback = std::function<void(long)>;

        PDFServerProcess(ProcessManager *mgr);

        void Start() override;

        void OnTerminate(int pid, int status) override;
        void OnPortFound(OnPortFoundCallback &&fun);

    protected:
        bool OnStdoutInputAvailable(const wxString &line) override;

    private:
        OnPortFoundCallback _port_found_cb;

        bool MatchPort(const wxString &line, long &port);
    };
}

#endif
