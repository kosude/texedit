cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project("texedit")

set(TE_DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/")
set(TE_TEXLIVE_DIR "${CMAKE_CURRENT_LIST_DIR}/texlive/")
set(TE_SCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/scripts/")

set(TE_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(CMAKE_MODULE_PATH "${TE_CMAKE_DIR}/mod/")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "Missing build configuration type! Defaulted to RELEASE, reconfigure project with option -DCMAKE_BUILD_TYPE=(Debug|Release)")
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TE_DEBUG true)
    set(TE_DEFINITIONS ${TE_DEFINITIONS} "_DEBUG")
endif()
if (WIN32)
    set(TE_DEFINITIONS ${TE_DEFINITIONS} "_WIN32")
elseif (APPLE)
    set(TE_DEFINITIONS ${TE_DEFINITIONS} "_APPLE")
elseif (UNIX)
    set(TE_DEFINITIONS ${TE_DEFINITIONS} "_UNIX")
endif()

# treating warnings as errors may be problematic when compiling for prod use.
# we are assuming here that lib users will be compiling in release config and lib developers/contributors in debug config.
if (TE_DEBUG)
    set(TE_COMPILE_OPTIONS
        -Wall -Wextra -Wpedantic -Werror
        -Wno-error=unused-parameter
        -Wno-error=unused-function)
endif()

set(CMAKE_C_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

set(TE_SRCS
    "src/compile.cpp"
    "src/main.cpp"
)
set(TE_TARGET_NAME "teexec")
add_executable(${TE_TARGET_NAME} ${TE_SRCS})
target_compile_options(${TE_TARGET_NAME} PRIVATE ${TE_COMPILE_OPTIONS})
target_compile_definitions(${TE_TARGET_NAME} PRIVATE ${TE_DEFINITIONS})
target_include_directories(${TE_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# zf_log v0.4.1
add_subdirectory("${TE_DEPS_DIR}/zf_log/" "${PROJECT_BINARY_DIR}/deps/zf_log/")
target_link_libraries(${TE_TARGET_NAME} zf_log)

add_custom_target(copy_texlive
    COMMAND ${CMAKE_COMMAND} -DIN_DIR:STRING="${TE_TEXLIVE_DIR}" -DOUT_DIR:STRING="texlive" -P "${TE_CMAKE_DIR}/copy_dir.cmake")
add_dependencies(${TE_TARGET_NAME} copy_texlive)

add_custom_target(copy_scripts
    COMMAND ${CMAKE_COMMAND} -DIN_DIR:STRING="${TE_SCRIPTS_DIR}" -DOUT_DIR:STRING="scripts" -P "${TE_CMAKE_DIR}/copy_dir.cmake")
add_dependencies(${TE_TARGET_NAME} copy_scripts)
