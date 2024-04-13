/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__url_open_hpp__
#define __texedit__url_open_hpp__

#include <string>

namespace te::util {
    const std::string GitHubUrl = "https://github.com/kosude/texedit";

    void OpenUrl(
        const std::string &url
    );
}

#endif
