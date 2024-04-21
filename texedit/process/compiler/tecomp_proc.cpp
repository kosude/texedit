/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "tecomp_proc.hpp"

#include "util/except.hpp"
#include "util/resources.hpp"

namespace te {
    TECompProcess::TECompProcess(ProcessManager &mgr) : _mgr{mgr}, _id{1} {
        _cmd = util::res::RelToExec("tecomp");
        if (!util::res::ValidateExecutable(_cmd.ToStdString())) {
            throw util::except::MissingComponentException("tecomp");
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
