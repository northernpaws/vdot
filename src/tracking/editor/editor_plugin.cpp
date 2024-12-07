
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include "editor_plugin.h"

void TrackingEditorPlugin::_bind_methods() {
}

TrackingEditorPlugin::~TrackingEditorPlugin() {
    if ( _panel != nullptr ) {
        _panel->queue_free();
    }
}

void TrackingEditorPlugin::_make_visible( bool visible ) {
    EditorPlugin::_make_visible( visible );

    if ( _panel != nullptr ) {
        _panel->set_visible( visible );
    }
}

void TrackingEditorPlugin::_enter_tree() {
    Node::_enter_tree();

    _panel = memnew( TrackingPluginPanel() );

    get_editor_interface()->get_editor_main_screen()->add_child( _panel );

    _make_visible( false );
}
void TrackingEditorPlugin::_exit_tree() {
    Node::_exit_tree();

    if ( _panel != nullptr ) {
        _panel->queue_free();
    }
}
