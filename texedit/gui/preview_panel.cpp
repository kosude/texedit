/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "preview_panel.hpp"

namespace te::gui {
    PreviewPanel::PreviewPanel(wxWindow *parent) : wxPanel(parent) {
        wxString pdf;
        _webView = wxWebView::New(this, wxID_ANY, "http://localhost:6950" + pdf);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_webView, 1, wxEXPAND);
        SetSizer(_sizer);
    }
}
