/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__except_hpp__
#define __texedit__except_hpp__

#include <string>

namespace te::util::except {
    class NotImplementedException : public std::exception {
    public:
        inline const char *what() const noexcept override {
            return "Attempted to invoke an operation that is not yet implemented.";
        }
    };
}

#endif
