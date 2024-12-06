## MacOS builds can target x86_64 and arm64, need to include both.
foreach(arch ${CMAKE_OSX_ARCHITECTURES})
    list(APPEND arch_libraries "${CUBISM_CORE_PATH}/lib/macos/${arch}/libLive2DCubismCore.a")
endforeach()

set(Live2DCubismCore_LIBRARY "${CMAKE_BINARY_DIR}/libs-gen/Live2DCubismCore-multiarch.a")

# To support the multi-arch build, we need to use `lipo` to merge the two
# architecture-specific binaries into a single multi-platform binary.
if(NOT TARGET Live2DCubismCore_MULTIARCH)
    add_custom_target(Live2DCubismCore_MULTIARCH
            DEPENDS ${arch_libraries}
            BYPRODUCTS Live2DCubismCore_LIBRARY
            COMMAND lipo ${arch_libraries} -create -output "Live2DCubismCore_LIBRARY"
    )
endif()

# Use the multi-arch library we've created as the source of the Cubism Core library.
add_library(Live2DCubismCore UNKNOWN IMPORTED)
add_dependencies(Live2DCubismCore Live2DCubismCore_MULTIARCH)
set_target_properties(Live2DCubismCore PROPERTIES
        IMPORTED_LOCATION "Live2DCubismCore_LIBRARY"
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${CUBISM_CORE_PATH}/include
)
