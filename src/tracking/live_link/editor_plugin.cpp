
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include "editor_plugin.h"

void LiveLinkEditorPlugin::_bind_methods() {

}

LiveLinkEditorPlugin::~LiveLinkEditorPlugin() {
    if (_panel != nullptr) {
        _panel->queue_free();
    }
}

void LiveLinkEditorPlugin::_make_visible( bool visible ) {
    EditorPlugin::_make_visible( visible );

    if (_panel != nullptr) {
        _panel->set_visible(visible);
    }
}


void LiveLinkEditorPlugin::_enter_tree() {
    Node::_enter_tree();

    _panel = memnew(LiveLinkPanel());

    get_editor_interface()->get_editor_main_screen()->add_child(_panel);

    _make_visible(false);
}
void LiveLinkEditorPlugin::_exit_tree() {
    Node::_exit_tree();

    if (_panel != nullptr) {
        _panel->queue_free();
    }
}

