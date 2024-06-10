/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__pdf_canvas_hpp__
#define __texedit__pdf_canvas_hpp__

#include "pdf_render/rendered_page.hpp"
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
        static constexpr int _page_gap = 25;

        std::vector<pdfr::RenderedPage> _rendered_pages{};

        void UpdateScrollbars();

        wxDECLARE_EVENT_TABLE();
    };
}

#endif
