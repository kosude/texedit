cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project("texedit")

set(TE_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(CMAKE_MODULE_PATH "${TE_CMAKE_DIR}/mod/")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "Missing build configuration type! Defaulted to RELEASE, reconfigure project with option -DCMAKE_BUILD_TYPE=(Debug|Release)")
    set(CMAKE_BUILD_TYPE Release)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TE_DEBUG true)
endif()

set(TE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set(TE_COMPILER "tecomp")
set(TE_COMPILER_DIR "${CMAKE_CURRENT_LIST_DIR}/src/compiler/")
add_subdirectory("${TE_COMPILER_DIR}")
