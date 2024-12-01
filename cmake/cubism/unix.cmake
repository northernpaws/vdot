add_library(Live2DCubismCore STATIC IMPORTED)

# Find library path.
set_target_properties(Live2DCubismCore
        PROPERTIES
        IMPORTED_LOCATION ${CUBISM_CORE_PATH}/lib/linux/x86_64/libLive2DCubismCore.a
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${CUBISM_CORE_PATH}/include
)
