/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__except_hpp__
#define __texedit__except_hpp__

#include <stdexcept>
#include <wx/string.h>

namespace te::except {
    class MissingComponentException : public std::runtime_error {
    public:
        inline MissingComponentException(const wxString &name)
            : std::runtime_error{"Missing " + name} {}
    };
}

#endif