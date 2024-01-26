find_package(Cargo REQUIRED)

set(CARGO_TOML "${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml")
set(CARGO_TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}")
if (NOT TE_DEBUG)
    set(CARGO_RELEASE_FLAG --release)
endif()

add_custom_target(
    ${TE_COMPILER}
    ALL ${CARGO_EXECUTABLE} +nightly build
        -Z unstable-options
        --manifest-path="${CARGO_TOML}"
        --target-dir="${CARGO_TARGET_DIR}"
        --out-dir="${CMAKE_CURRENT_BINARY_DIR}"
        ${CARGO_RELEASE_FLAG}
)

# copy TeX distribution to binary output
set(TE_TEXLIVE_DIR "${TE_ROOT}/disttex/")
add_custom_target(tecomp_cp_texlive
    COMMAND ${CMAKE_COMMAND} -DIN_DIR:STRING="${TE_TEXLIVE_DIR}" -DOUT_DIR:STRING="tex" -P "${TE_CMAKE_DIR}/copy_dir.cmake")
add_dependencies(${TE_COMPILER} tecomp_cp_texlive)

# copy program scripts to binary output
set(TE_COMPILER_SCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/scripts/")
add_custom_target(texcmp_cp_cmpscripts
    COMMAND ${CMAKE_COMMAND} -DIN_DIR:STRING="${TE_COMPILER_SCRIPTS_DIR}" -DOUT_DIR:STRING="." -P "${TE_CMAKE_DIR}/copy_dir.cmake")
add_dependencies(${TE_COMPILER} texcmp_cp_cmpscripts)
