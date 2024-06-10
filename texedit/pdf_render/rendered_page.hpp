/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__rendered_page_hpp__
#define __texedit__rendered_page_hpp__

#include <memory>

class wxImage;

namespace te::pdfr {
    struct RenderedPage {
    public:
        std::unique_ptr<wxImage> image;
        int page_width;
        int page_height;
    };
}

#endif
