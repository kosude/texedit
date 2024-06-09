/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__preview_pane_hpp__
#define __texedit__preview_pane_hpp__

#include <wx/wx.h>
#include <wx/webview.h>

#include "pane_base.hpp"
#include "gui/pdf_viewer/pdf_canvas.hpp"

namespace te::gui {
    class PreviewPane : public PaneBase {
    public:
        PreviewPane(wxWindow *parent);
        ~PreviewPane();

        void SetPDFLocation(const wxString &path);

    private:
        wxBoxSizer *_sizer;

        PDFDocument *_document{nullptr};
        PDFCanvas *_canvas;
    };
}

#endif
