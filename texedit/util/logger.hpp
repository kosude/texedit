/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__logger_hpp__
#define __texedit__logger_hpp__

#include <wx/log.h>
#include <wx/listbox.h>

namespace te::util {
    class GlobalLogger : public wxLogStderr {
    public:
        GlobalLogger(wxListBox *lb = nullptr);

        inline void SetListBox(wxListBox *lb) { _lbox = lb; }

    protected:
        void DoLogTextAtLevel(wxLogLevel level, const wxString &msg);

    private:
        wxListBox *_lbox;

        void AppendOutput(const wxString &msg);
    };
}

#endif
