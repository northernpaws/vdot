# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        Example.h
        Example.cpp
        GDExtensionTemplate.h
        GDExtensionTemplate.cpp
        register_extension.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
