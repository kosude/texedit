find_package(Cargo REQUIRED)

set(CARGO_TOML "${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml")
set(CARGO_TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}")
if (NOT TE_DEBUG)
    set(CARGO_RELEASE_FLAG --release)
endif()

add_custom_target(
    ${TE_FRONTEND}
    ALL ${CARGO_EXECUTABLE} +nightly build
        -Z unstable-options
        --manifest-path="${CARGO_TOML}"
        --target-dir="${CARGO_TARGET_DIR}"
        --out-dir="${CMAKE_CURRENT_BINARY_DIR}"
        ${CARGO_RELEASE_FLAG}
)
