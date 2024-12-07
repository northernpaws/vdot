

#ifndef VDOT_TRACKING_EDITOR_PLUGIN_H
#define VDOT_TRACKING_EDITOR_PLUGIN_H

#include <godot_cpp/classes/editor_plugin.hpp>

#include "tracking_plugin_panel.h"

class TrackingEditorPlugin : public godot::EditorPlugin {
    GDCLASS( TrackingEditorPlugin, godot::EditorPlugin )

    TrackingPluginPanel *_panel = nullptr;

  protected:
    static void _bind_methods();

  public:
    ~TrackingEditorPlugin();

    [[nodiscard]] godot::String _get_plugin_name() const override {
        return "Tracking";
    }

    [[nodiscard]] bool _has_main_screen() const override {
        return true;
    }

    // tODO: icon

    void _make_visible( bool visible ) override;

    void _enter_tree() override;
    void _exit_tree() override;
};

#endif // VDOT_TRACKING_EDITOR_PLUGIN_H
