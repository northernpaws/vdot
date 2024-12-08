# SPDX-License-Identifier: Unlicense

target_sources(${PROJECT_NAME}
        PRIVATE

        tracking/tracker.cpp
        tracking/tracker_face.cpp
        tracking/tracking_server.cpp
        tracking/tracking_interface.cpp

        tracking/editor/editor_plugin.cpp
        tracking/editor/tracking_plugin_panel.cpp
        tracking/editor/trackers/face_tracker_panel.cpp

        tracking/interfaces/live_link/live_link_server.cpp
        tracking/interfaces/live_link/live_link_panel.cpp
        tracking/interfaces/live_link/editor_plugin.cpp
        tracking/interfaces/live_link/live_link_interface.cpp
        tracking/interfaces/live_link/live_link_face_tracker.cpp

        tracking/interfaces/vts/vts_client.cpp

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
