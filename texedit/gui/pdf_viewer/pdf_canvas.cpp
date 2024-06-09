/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "pdf_canvas.hpp"

#include <wx/dcclient.h>
#include <wx/graphics.h>
#include <poppler-page.h>

#include <wx/rawbmp.h>

namespace te::gui {
    PDFCanvas::PDFCanvas(wxWindow *parent) : wxScrolledWindow{parent, wxID_ANY} {
        SetBackgroundColour(*wxRED);

        SetScrollbars(5, 50, 0, 100);
    }

    void PDFCanvas::RenderDocument(const PDFDocument *doc) {
        for (wxImage *img : _page_images) {
            delete img;
        }

        // render document into list of bitmaps
        _page_images = doc->RenderAll();
    }

    void PDFCanvas::OnPaint(wxPaintEvent &event) {
        wxPaintDC dc(this);
        DoPrepareDC(dc);

        int yi = 0;
        for (wxImage *img : _page_images) {
            wxBitmap bmp = wxBitmap(*img, 32);

            dc.DrawBitmap(bmp, 0, yi);

            yi++;
        }

        // wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
        // if (gc) {
        //     gc->SetPen(*wxGREY_PEN);
        //     gc->SetBrush(*wxLIGHT_GREY_BRUSH);
        //     gc->DrawRectangle(10, 10, 50, 500);
        //     gc->DrawEllipse(70, 10, 50, 700);

        //     delete gc;
        // }
    }

    wxBEGIN_EVENT_TABLE(PDFCanvas, wxScrolledWindow)
        EVT_PAINT(PDFCanvas::OnPaint)
    wxEND_EVENT_TABLE()
}
