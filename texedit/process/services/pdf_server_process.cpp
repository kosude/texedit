/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "pdf_server_process.hpp"
#include "util/resources.hpp"

#include <wx/regex.h>

namespace te::proc {
    PDFServerProcess::PDFServerProcess(ProcessManager *mgr) : Process(mgr) {
    }

    void PDFServerProcess::Start() {
        Process::StartHelper({
            util::RelToExec("tepdfserver").ToUTF8(),
            0
        });
    }

    void PDFServerProcess::OnTerminate(int pid, int status) {
        if (status == 1) {
            wxLogError("tepdfserver: PDF server init or runtime error (status %d)", status);
        }
    }

    void PDFServerProcess::OnPortFound(OnPortFoundCallback &&fun) {
        _port_found_cb = fun;
    }

    bool PDFServerProcess::OnStdoutInputAvailable(const wxString &line) {
        // check if the port is being output (will be matched against a regex query in MatchPort)
        // when it is, we can then use it to connect to the server from the GUI's webview (done via _port_found_cb)
        static long port = 0;
        if (port == 0 && MatchPort(line, port)) {
            _port_found_cb(port);
            return false;
        }

        return true;
    }

    bool PDFServerProcess::MatchPort(const wxString &line, long &port) {
        wxRegEx rex{"^tepdfserver:Port=([0-9]*)$"};
        wxString txt = line;

        wxString rets;
        long retl;

        while (rex.Matches(txt)) {
            size_t start, len;
            rex.GetMatch(&start, &len);

            rets = rex.GetMatch(txt, 1);
            if (!rets.IsEmpty()) {
                break;
            }

            txt = txt.Mid(start + len);
        }

        if (!rets.ToLong(&retl)) {
            wxLogError("Failed to convert string '%s' to long type", rets);
            return false;
        }

        // return retl into `port` if everything goes well
        port = retl;

        return true;
    }
}
