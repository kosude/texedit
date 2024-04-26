/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "compiler_process.hpp"
#include "except.hpp"
#include "util/resources.hpp"

namespace te::proc {
    CompilerProcess::CompilerProcess(ProcessManager *mgr) : Process(mgr, { util::RelToExec("tecomp").ToUTF8(), "watch", "examples", "examples/HelloWorld.tex", 0 }) {
    }

    std::vector<const char *> CompilerProcess::GetArgv() {
        static bool cmdset = false;
        if (!cmdset) {
            _cmd = util::RelToExec("tecomp");
            if (!util::ValidateExecutable(_cmd)) {
                throw except::MissingComponentException("tecomp");
            }
            cmdset = true;
        }

        return {};
    }
}
