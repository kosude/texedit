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
    //
    class MissingComponentException : public std::runtime_error {
    public:
        inline MissingComponentException(const wxString &name)
            : std::runtime_error{"Missing " + name} {}
    };

    class PDFException : public std::runtime_error {
    public:
        inline PDFException(const wxString &msg)
            : std::runtime_error{"PDF viewer: " + msg} {}
    };

    class PDFNotFoundException : public PDFException {
    public:
        inline PDFNotFoundException(const wxString &path)
            : PDFException{"Couldn't find PDF file at path " + path} {}
    };

    class PDFNotAccessibleException : public PDFException {
    public:
        inline PDFNotAccessibleException(const wxString &path)
            : PDFException{"Insufficient permissions to read locked PDF file at path " + path} {}
    };

    class InvalidPDFRenderException : public PDFException {
    public:
        inline InvalidPDFRenderException(const wxString &path)
            : PDFException{"Rendering PDF file at path " + path + " resulted in an invalid bitmap"} {}
    };
}

#endif
