/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "base_window.hpp"

namespace te {
    BaseWindow::BaseWindow(const std::string &title, uint32_t width, uint32_t height, uint32_t min_width, uint32_t min_height)
        : QWidget() {
        setWindowTitle(QString::fromStdString(title));
        resize(width, height);
        setMinimumSize(min_width, min_height);
    }

    BaseWindow::BaseWindow()
        : QWidget() {
    }
}
