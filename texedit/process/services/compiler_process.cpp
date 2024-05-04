/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "compiler_process.hpp"
#include "util/resources.hpp"

namespace te::proc {
    CompilerProcess::CompilerProcess(ProcessManager *mgr) : Process(mgr) {
    }

    void CompilerProcess::Start() {
        Process::StartHelper({
            util::RelToExec("tecomp").ToUTF8(),
            "watch", "examples", "examples/HelloWorld.tex",
            0
        });
    }
}
