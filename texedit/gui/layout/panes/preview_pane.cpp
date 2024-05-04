/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "preview_pane.hpp"

namespace te::gui {
    PreviewPane::PreviewPane(wxWindow *parent) : PaneBase(parent) {
        wxString pdf;
        _webView = wxWebView::New(this, wxID_ANY);

        _sizer = new wxBoxSizer(wxVERTICAL);
        _sizer->Add(_webView, 1, wxEXPAND);
        SetSizer(_sizer);
    }

    void PreviewPane::Load(const wxString &url) {
        wxLogInfo("Attempting to load preview resource from %s", url);
        _webView->LoadURL(url);
    }
}
