/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "pdf_server_process.hpp"
#include "except.hpp"
#include "util/resources.hpp"

namespace te::proc {
    PDFServerProcess::PDFServerProcess(ProcessManager *mgr) : Process(mgr, { util::RelToExec("tepdfserver").ToUTF8(), 0 }) {
        // TODO execute on known port
    }

    std::vector<const char *> PDFServerProcess::GetArgv() {
        static bool cmdset = false;
        if (!cmdset) {
            _cmd = util::RelToExec("tepdfserver");
            if (!util::ValidateExecutable(_cmd)) {
                throw except::MissingComponentException("tepdfserver");
            }
            cmdset = true;
        }

        return {
            _cmd.ToUTF8(),
            0
        };
    }
}
