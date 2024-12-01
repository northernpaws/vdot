
#include "godot_cpp/variant/callable.hpp"

#include "live_link_panel.h"

void LiveLinkPanel::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_connected" ),
                                 &LiveLinkPanel::_on_server_client_connected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_disconnected" ),
                                 &LiveLinkPanel::_on_server_client_disconnected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_updated" ),
                                 &LiveLinkPanel::_on_server_client_updated );
}

LiveLinkPanel::LiveLinkPanel() {
    _mesh = memnew( godot::MeshInstance3D );

    _server = memnew( LiveLinkServer );

    // we manually poll in relationship to if the panel is active or not.
    _server->_disable_polling = true;

    _server->connect( "client_connected", godot::Callable( this, "_on_server_client_connected" ) );
    _server->connect( "client_disconnected",
                      godot::Callable( this, "_on_server_client_disconnected" ) );
    _server->connect( "client_updated", godot::Callable( this, "_on_server_client_updated" ) );
}

LiveLinkPanel::~LiveLinkPanel() {
}

void LiveLinkPanel::_process( double delta ) {
    if ( _server_active ) {
        _server->poll();
    }
}

godot::StringName LiveLinkPanel::blend_shape_name(int i) {
    // TODO: optimize
    return godot::Array::make(
        "blend_shapes/eyeBlinkLeft",
        "blend_shapes/eyeLookDownLeft",
        "blend_shapes/eyeLookInLeft",
        "blend_shapes/eyeLookOutLeft",
        "blend_shapes/eyeLookUpLeft",
        "blend_shapes/eyeSquintLeft",
        "blend_shapes/eyeWideLeft",
        "blend_shapes/eyeBlinkRight",
        "blend_shapes/eyeLookDownRight",
        "blend_shapes/eyeLookInRight",
        "blend_shapes/eyeLookOutRight",
        "blend_shapes/eyeLookUpRight",
        "blend_shapes/eyeSquintRight",
        "blend_shapes/eyeWideRight",
        "blend_shapes/jawForward", "blend_shapes/jawRight",
        "blend_shapes/jawLeft", "blend_shapes/jawOpen",
        "blend_shapes/mouthClose", "blend_shapes/mouthFunnel",
        "blend_shapes/mouthPucker", "blend_shapes/mouthRight",
        "blend_shapes/mouthLeft",
        "blend_shapes/mouthSmileLeft",
        "blend_shapes/mouthSmileRight",
        "blend_shapes/mouthFrownLeft",
        "blend_shapes/mouthFrownRight",
        "blend_shapes/mouthDimpleLeft",
        "blend_shapes/mouthDimpleRight",
        "blend_shapes/mouthStretchLeft",
        "blend_shapes/mouthStretchRight",
        "blend_shapes/mouthRollLower",
        "blend_shapes/mouthRollUpper",
        "blend_shapes/mouthShrugLower",
        "blend_shapes/mouthShrugUpper",
        "blend_shapes/mouthPressLeft",
        "blend_shapes/mouthPressRight",
        "blend_shapes/mouthLowerDownLeft",
        "blend_shapes/mouthLowerDownRight",
        "blend_shapes/mouthUpperUpLeft",
        "blend_shapes/mouthUpperUpRight",
        "blend_shapes/browDownLeft",
        "blend_shapes/browDownRight",
        "blend_shapes/browInnerUp",
        "blend_shapes/browOuterUpLeft",
        "blend_shapes/browOuterUpRight",
        "blend_shapes/cheekPuff",
        "blend_shapes/cheekSquintLeft",
        "blend_shapes/cheekSquintRight",
        "blend_shapes/noseSneerLeft",
        "blend_shapes/noseSneerRight",
        "blend_shapes/tongueOut", "blend_shapes/headYaw",
        "blend_shapes/headPitch", "blend_shapes/headRoll",
        "blend_shapes/leftEyeYaw",
        "blend_shapes/leftEyePitch",
        "blend_shapes/leftEyeRoll",
        "blend_shapes/rightEyeYaw",
        "blend_shapes/rightEyePitch",
        "blend_shapes/rightEyeRoll" )[i];
}

void LiveLinkPanel::update_mesh( const LiveLinkClientData *data ) {
    //    auto rotation = godot::Vector3(
    //                        - data->_get_head_pitch(),
    //                        data->_get_head_yaw(),
    //                        data->_get_head_roll()) * 0.1;

    for ( int i = 0; i < data->_data.size(); ++i ) {
        auto value = data->_data[i];
        auto shape = _mesh->find_blend_shape_by_name( blend_shape_name(i) );
        _mesh->set_blend_shape_value( shape, value );
    }
}

void LiveLinkPanel::_on_server_client_connected( LiveLinkClient *client ) {
}

void LiveLinkPanel::_on_server_client_disconnected( LiveLinkClient *client ) {
}

void LiveLinkPanel::_on_server_client_updated( LiveLinkClient *client ) {
    update_mesh( client->_values );
}