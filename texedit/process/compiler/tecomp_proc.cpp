/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "tecomp_proc.hpp"

#include "except.hpp"
#include "util/resources.hpp"

namespace te::proc {
    TECompProcess::TECompProcess(ProcessManager &mgr) : _mgr{mgr}, _id{1} {
        _cmd = util::RelToExec("tecomp");
        if (!util::ValidateExecutable(_cmd)) {
            throw except::MissingComponentException("tecomp");
        }
    }

    void TECompProcess::Start() {
        const char *const argv[] = {
            _cmd.ToUTF8(),
            "watch", "examples", "examples/HelloWorld.tex",
            0
        };

        _mgr.ExecutePipedAsync(_id, argv);
    }
}
