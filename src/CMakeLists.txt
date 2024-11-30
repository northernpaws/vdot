# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        tracking/arkit/blend_shapes.h
        tracking/arkit/blend_shapes.cpp
        tracking/live_link/live_link_server.h
        tracking/live_link/live_link_server.cpp
        tracking/live_link/live_link_panel.h
        tracking/live_link/live_link_panel.cpp
        vdot.h
        vdot.cpp
        register_extension.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
