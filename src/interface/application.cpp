/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include "application.hpp"

#include "util/log.hpp"

namespace te {
    TexEditApplication::TexEditApplication(int &argc, char **argv)
        : QApplication(argc, argv) {
        LINFO("TexEdit interface application started");
        LINFO("platformName = %s", platformName().toStdString().c_str());

        _editor = std::make_unique<EditorView>();
        _editor->show();
    }

    TexEditApplication::~TexEditApplication() {
    }

    void TexEditApplication::Quit() {
        LINFO("TexEdit interface application quit");
        QApplication::quit();
    }
}
