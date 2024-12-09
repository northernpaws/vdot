

#include "vts_client.h"
#include <godot_cpp/classes/json.hpp>

void VTSData::_bind_methods() {
}

VTSData::VTSData() {
    _empty_vec3["x"] = 0.0f;
    _empty_vec3["y"] = 0.0f;
    _empty_vec3["z"] = 0.0f;
}

VTSData::~VTSData() = default;

godot::Error VTSData::decode_packet( const godot::PackedByteArray &packet ) {
    godot::Ref<godot::JSON> decoded = memnew( godot::JSON );
    auto err = decoded->parse( packet.get_string_from_utf8() );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err,
                         godot::vformat( "Received invalid JSON from VTS server: %s",
                                         decoded->get_error_message() ) );

    godot::Dictionary data = decoded->get_data();

    timestamp = data.get( "Timestamp", 0 );

    hotkey = data.get( "Hotkey", -1 );

    face_found = data.get( "FaceFound", false );

    godot::Dictionary head_position_dict = data.get( "Position", _empty_vec3 );
    head_position =
        godot::Vector3( head_position_dict["x"], head_position_dict["y"], head_position_dict["z"] );

    godot::Dictionary head_rotation_dict = data.get( "Rotation", _empty_vec3 );
    head_rotation =
        godot::Vector3( head_rotation_dict["x"], head_rotation_dict["y"], head_rotation_dict["z"] );

    godot::Dictionary left_eye_rotation_dict = data.get( "EyeLeft", _empty_vec3 );
    eye_rotation_left = godot::Vector3( left_eye_rotation_dict["x"], left_eye_rotation_dict["y"],
                                        left_eye_rotation_dict["z"] );

    godot::Dictionary right_eye_rotation_dict = data.get( "EyeRight", _empty_vec3 );
    eye_rotation_right = godot::Vector3( right_eye_rotation_dict["x"], right_eye_rotation_dict["y"],
                                         right_eye_rotation_dict["z"] );

    godot::Array blend_shapes = data.get( "BlendShapes", {} );
    for ( int i = 0; i < blend_shapes.size(); i++ ) {
        godot::Dictionary blend_shape = blend_shapes[i];
        godot::StringName key = blend_shape.get( "k", "" );
        float value = blend_shape.get( "v", 0.0f );

        weights[ARKit::ShapeNames[key]] = value;
    }

    return godot::OK;
}

void VTSClient::_bind_methods() {
}

VTSClient::VTSClient() {
    _data = godot::Ref<VTSData>( memnew( VTSData ) );
}

VTSClient::~VTSClient() = default;

godot::Error VTSClient::connect() {
    ERR_FAIL_COND_V_MSG( _client != nullptr, godot::FAILED, "Client is already running." );

    // First, build the request packet we send repeatedly to request new tracking datga.
    godot::Dictionary packet;
    packet["messageType"] = "iOSTrackingDataRequest";
    packet["time"] = 1.0f; // between 0.5 and 10 seconds
    packet["sentBy"] = "vdot";

    godot::Array ports;
    ports.append( _port );
    packet["ports"] = ports;

    auto json = godot::JSON::stringify( packet );
    _request_packet = json.to_utf8_buffer();

    // Set up the client.
    _client = memnew( godot::PacketPeerUDP );
    _client->set_broadcast_enabled( true );
    _client->set_dest_address( _address, _port );

    // Attempt to connect to the host.
    auto err = _client->connect_to_host( _address, _port );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to connect to host." );

    return godot::OK;
}

void VTSClient::disconnect() {
    if ( _client != nullptr ) {
        _client->close();
    }
}

godot::Error VTSClient::receive() {
    // Send the packet to instruct the server we're still here and still want data.
    auto err = _client->put_packet( _request_packet );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to connect to host." );

    if ( _client->get_available_packet_count() < 1 ) {
        return godot::OK;
    }

    ERR_FAIL_COND_V_MSG( _client->get_packet_error() != godot::OK, _client->get_packet_error(),
                         "Packet error." );

    // TODO: do we need to flush other packets?

    auto packet = _client->get_packet();
    if ( packet.size() == 0 ) {
        return godot::OK;
    }

    err = _data->decode_packet( packet );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err,
                         godot::vformat( "Failed to decode packet from VTS server" ) );

    // TODO: update signal

    return godot::OK;
}
