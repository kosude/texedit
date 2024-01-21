/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include "windows/editor_view.hpp"

#include <QApplication>

namespace te {
    class TexEditApplication : public QApplication {
    public:
        TexEditApplication(int &argc, char **argv);
        ~TexEditApplication();

        void Quit();

    private:
        std::unique_ptr<EditorView> _editor;
    };
}
