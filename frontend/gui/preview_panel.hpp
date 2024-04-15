/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__preview_panel_hpp__
#define __texedit__preview_panel_hpp__

#include <wx/wx.h>
#include <wx/webview.h>

namespace te {
    class PreviewPanel : public wxPanel {
    public:
        PreviewPanel(wxWindow *parent);

    private:
        wxBoxSizer *_sizer;

        wxWebView *_webView;
    };
}

#endif
