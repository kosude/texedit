set(SRCS
    "main.cpp"
)
set(TARGET_NAME "texeditexec")

add_executable(${TARGET_NAME} ${SRCS})

target_compile_options(${TARGET_NAME} PRIVATE ${TE_COMPILE_OPTIONS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${TE_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# zf_log v0.4.1
add_subdirectory("${TE_DEPS_DIR}/zf_log/" "${PROJECT_BINARY_DIR}/deps/zf_log/")
target_link_libraries(${TARGET_NAME} zf_log)
