# SPDX-License-Identifier: Unlicense

target_sources(${PROJECT_NAME}
        PRIVATE

        tracking/arkit/blend_shapes.cpp
        tracking/live_link/live_link_server.cpp
        tracking/live_link/live_link_panel.cpp

        models/live2d/renderer/cubism_renderer.cpp
        models/live2d/renderer/cubism_renderer_2d.cpp
        models/live2d/renderer/cubism_model_proxy.cpp
        models/live2d/renderer/cubism_renderer_impl.cpp
        models/live2d/cubism_effect.cpp
        models/live2d/cubism_model.cpp

        vdot.h
        vdot.cpp
        register_extension.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "src"
)
