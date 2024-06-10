/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "pdf_document.hpp"

#include "except.hpp"

#include <wx/log.h>
#include <wx/image.h>

namespace te::pdfr {
    PDFDocument::PDFDocument(const wxString &path) : _path{path} {
        _renderer.set_render_hints(
            poppler::page_renderer::antialiasing |
            poppler::page_renderer::text_antialiasing
        );

        _doc = poppler::document::load_from_file(_path.ToStdString());
        if (!_doc) {
            throw new except::PDFNotFoundException(_path);
        }
        if (_doc->is_locked()) {
            throw new except::PDFNotAccessibleException(_path);
        }

        // create and store representations of each page in the document
        int pagen = _doc->pages();
        _pages.resize(pagen);
        for (int i = 0; i < pagen; i++) {
            _pages[i] = _doc->create_page(i);
        }
    }

    std::vector<RenderedPage> PDFDocument::RenderAll() const {
        int pagen = _pages.size();
        std::vector<RenderedPage> ret(pagen);

        int i = 0;
        for (poppler::page *page : _pages) {
            // TODO: preference for PDF rendering DPI
            poppler::image img = _renderer.render_page(page, 54, 54);
            if (!img.is_valid()) {
                throw new except::InvalidPDFRenderException(_path);
            }
            wxLogMessage("PDF: rendered page i=%d to image of size %dx%d, format enum %d", i, img.width(), img.height(), img.format());

            // Now we convert poppler's colour ordering to the completely idiotic format WxImage wants, which is separate arrays of RGB and A...

            unsigned char *rgb = (unsigned char *) malloc(sizeof(unsigned char) * img.width() * img.height() * 3);
            unsigned char *a = (unsigned char *) malloc(sizeof(unsigned char) * img.width() * img.height());

            int width = img.width(),
                height = img.height();
            int dims = width * height;
            char *data = img.data();

            for (int j = 0, k = 0; k < dims; j += 4, k++) {
                // Colours are being read in ABGR format even though Poppler reports the image as ARGB (???)
                // Anyways this works, so until it causes problems, don't touch it
                a[k]           = data[j + 3];
                rgb[j - k]     = data[j + 2];
                rgb[j + 1 - k] = data[j + 1];
                rgb[j + 2 - k] = data[j];
            }

            ret[i] = RenderedPage {
                std::make_unique<wxImage>(width, height, rgb, a, false),
                width,
                height
            };

            i++;
        }

        return ret;
    }
}
