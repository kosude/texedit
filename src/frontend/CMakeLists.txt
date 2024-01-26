if (TE_DEBUG)
    set(TE_DOTNET_CFG DEBUG)
else()
    set(TE_DOTNET_CFG RELEASE)
endif()

add_custom_target(
    ${TE_FRONTEND}
    ALL dotnet build
        "${CMAKE_CURRENT_SOURCE_DIR}/TexEdit.csproj"
        --output "${CMAKE_CURRENT_BINARY_DIR}/"
)
