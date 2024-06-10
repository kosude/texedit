/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "preview_pane.hpp"

#include "except.hpp"

#include "pdf_render/pdf_document.hpp"

namespace te::gui {
    PreviewPane::PreviewPane(wxWindow *parent) : PaneBase(parent) {
        _canvas = new PDFCanvas(this);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_canvas, 1, wxEXPAND, 3);
        SetSizer(_sizer);
    }

    PreviewPane::~PreviewPane() {
        // delete last loaded document if applicable
        if (_document) {
            delete _document;
        }
    }

    void PreviewPane::SetPDFLocation(const wxString &path) {
        try {
            // document is heap-allocated, so replace it here
            if (_document) {
                delete _document;
            }
            _document = new pdfr::PDFDocument(path);

            // RenderDocument() stores the new document's rendered images into the canvas object to be drawn later
            _canvas->RenderDocument(_document);
        } catch (except::PDFException *e) {
            // TODO: show error message in the preview pane.
            wxLogError("%s", e->what());
            return;
        }
    }
}
