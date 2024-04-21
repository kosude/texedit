/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__tecomp_proc_hpp__
#define __texedit__tecomp_proc_hpp__

#include <wx/wx.h>

#include "process/process_mgr.hpp"

namespace te::proc {
    class TECompProcess {
    public:
        TECompProcess(ProcessManager &mgr);

        void Start();

        inline int GetID() { return _id; }

    private:
        ProcessManager &_mgr;
        wxString _cmd;

        int _id;
    };
}

#endif
