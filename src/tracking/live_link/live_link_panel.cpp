
#include "godot_cpp/variant/callable.hpp"

#include "live_link_panel.h"

void LiveLinkPanel::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_server_client_connected"), &LiveLinkPanel::_on_server_client_connected);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_server_client_disconnected"), &LiveLinkPanel::_on_server_client_disconnected);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_server_client_updated"), &LiveLinkPanel::_on_server_client_updated);
}

LiveLinkPanel::LiveLinkPanel() {
    _mesh = memnew(godot::MeshInstance3D);


    _server = memnew(LiveLinkServer);

    // we manually poll in relationship to if the panel is active or not.
    _server->_disable_polling = true;

    _server->connect("client_connected", godot::Callable(this, "_on_server_client_connected"));
    _server->connect("client_disconnected", godot::Callable(this, "_on_server_client_disconnected"));
    _server->connect("client_updated", godot::Callable(this, "_on_server_client_updated"));
}

LiveLinkPanel::~LiveLinkPanel() {

}

void LiveLinkPanel::_process(double delta) {
    if (_server_active) {
        _server->poll();
    }
}

void LiveLinkPanel::update_mesh(const LiveLinkClientData* data) {
//    auto rotation = godot::Vector3(
//                        - data->_get_head_pitch(),
//                        data->_get_head_yaw(),
//                        data->_get_head_roll()) * 0.1;

    for ( int i = 0; i < data->_data.size(); ++i ) {
        auto value = data->_data[i];
        auto shape = _mesh->find_blend_shape_by_name(LiveLinkClientData::key_map[i]);
        _mesh->set_blend_shape_value(shape, value);
    }
}

void LiveLinkPanel::_on_server_client_connected (LiveLinkClient* client) {

}

void LiveLinkPanel::_on_server_client_disconnected (LiveLinkClient* client) {

}

void LiveLinkPanel::_on_server_client_updated (LiveLinkClient* client) {
    update_mesh(client->_values);
}