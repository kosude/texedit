/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include "base/base_window.hpp"

#include "ui_editor_view.h"

namespace te {
    class EditorView : public BaseWindow, private Ui::EditorView {
        Q_OBJECT

    public:
        EditorView();
        ~EditorView();
    };
}
