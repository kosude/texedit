/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "pdf_canvas.hpp"

#include "pdf_render/pdf_document.hpp"

#include <wx/dcclient.h>

namespace te::gui {
    PDFCanvas::PDFCanvas(wxWindow *parent) : wxScrolledWindow{parent, wxID_ANY} {
        SetScrollbars(5, 50, 0, 100);
    }

    void PDFCanvas::RenderDocument(const pdfr::PDFDocument *doc) {
        // render document into list of bitmaps
        _rendered_pages = doc->RenderAll();
    }

    void PDFCanvas::OnPaint(wxPaintEvent &event) {
        wxPaintDC dc(this);
        DoPrepareDC(dc);

        int yi = 0;
        for (const pdfr::RenderedPage &page : _rendered_pages) {
            // images have to be converted to a bitmap before being drawn
            wxBitmap bmp = wxBitmap(*page.image, 32);
            dc.DrawBitmap(bmp, 0, yi);

            yi += page.page_height + 50;
        }
    }

    wxBEGIN_EVENT_TABLE(PDFCanvas, wxScrolledWindow)
        EVT_PAINT(PDFCanvas::OnPaint)
    wxEND_EVENT_TABLE()
}
