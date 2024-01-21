/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include <QWidget>

namespace te {
    class BaseWindow : public QWidget {
        Q_OBJECT

    public:
        BaseWindow(const std::string &title, uint32_t width, uint32_t height, uint32_t min_width, uint32_t min_height);
        BaseWindow();
    };
}
