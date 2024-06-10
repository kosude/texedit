cmake_minimum_required(VERSION 3.24)

project("texedit" CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake/mod")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        set(COMPILE_OPTIONS
            /W4 /WX)
    else()
        set(COMPILE_OPTIONS
            -Wall -Wextra -pedantic -Werror
            -Wno-error=unused-parameter
            -Wno-error=unused-function
            -Wno-implicit-fallthrough)
    endif()
endif()

set(TARGET_NAME "${PROJECT_NAME}")
set(DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/../deps/")

set(SRCS
    "gui/editor/src_editor_component.cpp"
    "gui/layout/panes/editor_pane.cpp"
    "gui/layout/panes/explorer_pane.cpp"
    "gui/layout/panes/output_pane.cpp"
    "gui/layout/panes/preview_pane.cpp"
    "gui/layout/layout_manager.cpp"
    "gui/pdf_viewer/pdf_canvas.cpp"
    "gui/main_frame.cpp"
    "gui/prog_info.cpp"

    "pdf_render/pdf_document.cpp"
    "pdf_render/poppler_log.cpp"

    "process/services/compiler_process.cpp"
    "process/process_manager.cpp"
    "process/process.cpp"

    "util/logger.cpp"
    "util/resources.cpp"

    "main.cpp"
)

# wxwidgets
find_package(wxWidgets REQUIRED COMPONENTS core base stc webview aui)
include(${wxWidgets_USE_FILE})

# libpoppler
find_package(Poppler REQUIRED COMPONENTS Cpp)

# build executable
add_executable(${TARGET_NAME} ${SRCS})
target_include_directories(${TARGET_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    ${Poppler_INCLUDE_DIRS}
)
target_link_libraries(${TARGET_NAME}
    ${wxWidgets_LIBRARIES}
    ${Poppler_LIBRARIES}
)
target_compile_definitions(${TARGET_NAME} PRIVATE
    TEXEDIT_VERSION="${TEXEDIT_VERSION}"
    ${Poppler_DEFINITIONS}
)
