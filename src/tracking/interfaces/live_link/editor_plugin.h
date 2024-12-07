

#ifndef VDOT_EDITOR_PLUGIN_H
#define VDOT_EDITOR_PLUGIN_H

#include <godot_cpp/classes/editor_plugin.hpp>

#include "live_link_panel.h"

class LiveLinkEditorPlugin : public godot::EditorPlugin {
    GDCLASS( LiveLinkEditorPlugin, godot::EditorPlugin )

    LiveLinkPanel *_panel;

  protected:
    static void _bind_methods();

  public:
    ~LiveLinkEditorPlugin();

    [[nodiscard]] godot::String _get_plugin_name() const override {
        return "LiveLink";
    }

    [[nodiscard]] bool _has_main_screen() const override {
        return true;
    }

    // tODO: icon

    void _make_visible( bool visible ) override;

    void _enter_tree() override;
    void _exit_tree() override;
};

#endif // VDOT_EDITOR_PLUGIN_H
