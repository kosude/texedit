/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__preview_pane_hpp__
#define __texedit__preview_pane_hpp__

#include "pane_base.hpp"
#include "gui/pdf_viewer/pdf_canvas.hpp"

#include <wx/wx.h>
#include <wx/webview.h>
#include <memory>

namespace te::pdfr {
    class PDFDocument;
}

namespace te::gui {
    class PreviewPane : public PaneBase {
    public:
        PreviewPane(wxWindow *parent);
        ~PreviewPane();

        void SetPDFLocation(const wxString &path);

    private:
        wxBoxSizer *_sizer;

        std::unique_ptr<pdfr::PDFDocument> _document{nullptr};
        PDFCanvas *_canvas;
    };
}

#endif
