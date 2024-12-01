add_library(Live2DCubismCore STATIC IMPORTED)

# Detect architecture.
if(CMAKE_EXE_LINKER_FLAGS STREQUAL "/machine:x64")
    set(ARCH x86_64)
elseif(CMAKE_EXE_LINKER_FLAGS STREQUAL "/machine:X86")
    set(ARCH x86)
else()
    message(FATAL_ERROR "[${APP_NAME}] Invalid linker flag ${CMAKE_EXE_LINKER_FLAGS}.")
endif()

# Detect compiler.
if(MSVC_VERSION MATCHES 1800)
    # Visual Studio 2013
    set(COMPILER 120)
elseif(MSVC_VERSION MATCHES 1900)
    # Visual Studio 2015
    set(COMPILER 140)
elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS 1920)
    # Visual Studio 2017
    set(COMPILER 141)
elseif(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS 1930)
    # Visual Studio 2019
    set(COMPILER 142)
elseif(MSVC_VERSION GREATER_EQUAL 1930 AND MSVC_VERSION LESS 1940)
    # Visual Studio 2022
    set(COMPILER 143)
elseif(MSVC)
    message(FATAL_ERROR "[${APP_NAME}] Unsupported Visual C++ compiler used. MSVC_VERSION: ${MSVC_VERSION}")
else()
    message(FATAL_ERROR "[${APP_NAME}] Unsupported compiler used.")
endif()

# Detect core crt.
if(CORE_CRL_MD)
    set(CRT MD)
else()
    set(CRT MT)
endif()

# Find library path.
set(CORE_LIB_SUFFIX ${CUBISM_CORE_PATH}/lib/windows/${ARCH}/${COMPILER})
set_target_properties(Live2DCubismCore
        PROPERTIES
        IMPORTED_LOCATION_DEBUG
        ${CUBISM_CORE_LIB_SUFFIX}/Live2DCubismCore_${CRT}d.lib
        IMPORTED_LOCATION_RELEASE
        ${CUBISM_CORE_LIB_SUFFIX}/Live2DCubismCore_${CRT}.lib
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${CUBISM_CORE_PATH}/include
)