cmake_minimum_required(VERSION 3.24)

project("texedit" CXX)

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
    "gui/editor_panel.cpp"
    "gui/main_frame.cpp"
    "util/log.cpp"
    "main.cpp"
)

# cutils
add_subdirectory("${DEPS_DIR}/cutils" "${CMAKE_CURRENT_BINARY_DIR}/deps/cutils")

# wxwidgets
find_package(wxWidgets REQUIRED COMPONENTS core base stc)
include(${wxWidgets_USE_FILE})

# build executable
add_executable(${TARGET_NAME} ${SRCS})
target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(${TARGET_NAME}
    cutils
    ${wxWidgets_LIBRARIES})
