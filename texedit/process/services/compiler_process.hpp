/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__compiler_process_hpp__
#define __texedit__compiler_process_hpp__

#include <wx/wx.h>

#include "process/process.hpp"

namespace te::proc {
    class CompilerProcess : public Process {
    public:
        CompilerProcess(ProcessManager *mgr);

        void Start() override;
    };
}

#endif
