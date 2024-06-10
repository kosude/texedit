/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_canvas_hpp__
#define __texedit__pdf_canvas_hpp__

#include <wx/scrolwin.h>
#include <wx/image.h>
#include <vector>

namespace te::pdfr {
    class PDFDocument;
}

namespace te::gui {
    class PDFCanvas : public wxScrolledWindow {
    public:
        PDFCanvas(wxWindow *parent);

        void RenderDocument(const pdfr::PDFDocument *doc);

        void OnPaint(wxPaintEvent &event);

    private:
        std::vector<wxImage *> _page_images{};

        wxDECLARE_EVENT_TABLE();
    };
}

#endif
