# SPDX-License-Identifier: Unlicense

target_sources(${PROJECT_NAME}
        PRIVATE

        tracking/tracker.cpp
        tracking/tracker_face.cpp
        tracking/tracking_server.cpp
        tracking/tracking_interface.cpp
        tracking/tracking_manager_node.cpp

        tracking/standards/arkit_blend_shapes.cpp
        tracking/standards/unified_expressions.cpp

        tracking/editor/editor_plugin.cpp
        tracking/editor/tracking_plugin_panel.cpp
        tracking/editor/trackers/face_tracker_panel.cpp

        models/model.cpp
        models/2d/model_2d.cpp
        models/model_parameter.cpp

        avatar/avatar_parameter.cpp
        avatar/avatar.cpp

        tracking/interfaces/live_link/live_link_server.cpp
        tracking/interfaces/live_link/live_link_panel.cpp
        tracking/interfaces/live_link/editor_plugin.cpp
        tracking/interfaces/live_link/live_link_interface.cpp
        tracking/interfaces/live_link/live_link_face_tracker.cpp

        tracking/interfaces/vts/vts_client.cpp
        tracking/interfaces/vts/vts_face_tracker.cpp
        tracking/interfaces/vts/vts_interface.cpp

        models/2d/live2d/renderer/cubism_renderer.cpp
        models/2d/live2d/renderer/cubism_renderer_2d.cpp
        models/2d/live2d/renderer/cubism_model_proxy.cpp
        models/2d/live2d/renderer/cubism_renderer_impl.cpp
        models/2d/live2d/cubism_effect.cpp
        models/2d/live2d/cubism_model.cpp

        vdot.h
        vdot.cpp
        register_extension.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "src"
        ${CMAKE_CURRENT_LIST_DIR}
)

include_directories(${CMAKE_CURRENT_LIST_DIR})
