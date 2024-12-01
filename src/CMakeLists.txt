# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        tracking/arkit/blend_shapes.h
        tracking/arkit/blend_shapes.cpp
        tracking/live_link/live_link_server.h
        tracking/live_link/live_link_server.cpp
        tracking/live_link/live_link_panel.h
        tracking/live_link/live_link_panel.cpp

        models/live2d/cubism.h
        models/live2d/renderer/cubism_renderer.h
        models/live2d/renderer/cubism_renderer.cpp
        models/live2d/renderer/cubism_renderer_2d.h
        models/live2d/renderer/cubism_renderer_2d.cpp
        models/live2d/renderer/cubism_model_proxy.h
        models/live2d/renderer/cubism_model_proxy.cpp
        models/live2d/renderer/cubism_renderer_impl.cpp
        models/live2d/cubism_motion_entry.h
        models/live2d/cubism_value_abs.h
        models/live2d/cubism_value_parameter.h
        models/live2d/cubism_value_part_opacity.h
        models/live2d/cubism_effect.h
        models/live2d/cubism_effect.cpp
        models/live2d/cubism_effect_breath.h
        models/live2d/cubism_effect_custom.h
        models/live2d/cubism_effect_eye_blink.h
        models/live2d/cubism_effect_hit_area.h
        models/live2d/cubism_effect_target_point.h
        models/live2d/cubism_model.h
        models/live2d/cubism_model.cpp

        vdot.h
        vdot.cpp
        register_extension.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
