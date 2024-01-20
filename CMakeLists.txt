cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project("texedit")

set(TE_DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "Missing build configuration type! Defaulted to RELEASE, reconfigure project with option -DCMAKE_BUILD_TYPE=(Debug|Release)")
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TE_DEBUG true)
    set(TE_DEFINITIONS ${TE_DEFINITIONS} "_DEBUG")
endif()

# treating warnings as errors may be problematic when compiling for prod use.
# we are assuming here that lib users will be compiling in release config and lib developers/contributors in debug config.
if (TE_DEBUG)
    set(TE_COMPILE_OPTIONS
        -Wall -Wextra -Wpedantic -Werror
        -Wno-error=unused-parameter
        -Wno-error=unused-function)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/" "${CMAKE_CURRENT_BINARY_DIR}/texedit/")
