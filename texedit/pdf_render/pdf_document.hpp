/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_document_hpp__
#define __texedit__pdf_document_hpp__

#include <vector>

#include <wx/string.h>
#include <wx/bitmap.h>
#include <poppler-document.h>
#include <poppler-page-renderer.h>

namespace te::pdfr {
    /**
     * An abstraction over a `libpoppler` PDF document and associated functionality.
     */
    class PDFDocument {
    public:
        PDFDocument(const wxString &path);

        // Render all pages in the document into a vector of wxImages (note they must be freed after this).
        std::vector<wxImage *> RenderAll() const;

    private:
        const wxString &_path;

        poppler::page_renderer _renderer;

        poppler::document *_doc;
        std::vector<poppler::page *> _pages;
    };
}

#endif
