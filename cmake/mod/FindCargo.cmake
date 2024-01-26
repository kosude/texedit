# Copyright (c) 2022 Andrew Lilley Brinker.

# Find Cargo, possibly in ~/.cargo. Make sure to check in any `bin` subdirectories
# on the program search path
# TODO: Remove the Unix-ism ($ENV{HOME}) and replace it with something platform-agnostic.
find_program(CARGO_EXECUTABLE cargo PATHS "$ENV{HOME}/.cargo" PATH_SUFFIXES bin)

set(CARGO_CHANNEL "nightly")

if(CARGO_EXECUTABLE)
    execute_process(COMMAND ${CARGO_EXECUTABLE} -V OUTPUT_VARIABLE CARGO_CHANNEL_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(CARGO_CHANNEL_OUTPUT MATCHES "cargo [0-9]+\\.[0-9]+\\.[0-9]+-([a-zA-Z]*).*")
        set(CARGO_CHANNEL ${CMAKE_MATCH_1})
    endif()
endif()

# Hides the CARGO_EXECUTABLE variable unless advanced variables are requested
mark_as_advanced(CARGO_EXECUTABLE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Cargo
    REQUIRED_VARS
        CARGO_CHANNEL
        CARGO_EXECUTABLE
)
