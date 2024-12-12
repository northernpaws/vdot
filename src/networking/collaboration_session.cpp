
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/e_net_packet_peer.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "collaboration_session.h"

void CollaborationSession::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "peer_connected", godot::PropertyInfo( godot::Variant::OBJECT, "peer",
                                               godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                               CollaborationPeer::get_class_static() ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "peer_disconnected", godot::PropertyInfo( godot::Variant::OBJECT, "peer",
                                                  godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                  CollaborationPeer::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo(
        "local_avatar_added", godot::PropertyInfo( godot::Variant::OBJECT, "avatar",
                                                   godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                   Avatar::get_class_static() ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "local_avatar_removed", godot::PropertyInfo( godot::Variant::OBJECT, "avatar",
                                                     godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                     Avatar::get_class_static() ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "start_server" ),
                                 &CollaborationSession::start_server );
    godot::ClassDB::bind_method( godot::D_METHOD( "connect_to_server", "address", "port" ),
                                 &CollaborationSession::connect_to_server );

    godot::ClassDB::bind_method( godot::D_METHOD( "_client_connected_to_server" ),
                                 &CollaborationSession::_client_connected_to_server );
    godot::ClassDB::bind_method( godot::D_METHOD( "_client_connection_failed" ),
                                 &CollaborationSession::_client_connection_failed );
    godot::ClassDB::bind_method( godot::D_METHOD( "_client_server_disconnected" ),
                                 &CollaborationSession::_client_server_disconnected );

    godot::ClassDB::bind_method( godot::D_METHOD( "_peer_connected", "peer_id" ),
                                 &CollaborationSession::_peer_connected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_peer_disconnected", "peer_id" ),
                                 &CollaborationSession::_peer_disconnected );
}

CollaborationSession::CollaborationSession() {
    local_peer = godot::Ref<CollaborationPeer>( memnew( CollaborationPeer ) );
}

void CollaborationSession::_ready() {
    get_multiplayer()->set_multiplayer_peer( local_peer );

    get_multiplayer()->connect( "peer_connected", godot::Callable( this, "_peer_connected" ) );
    get_multiplayer()->connect( "peer_disconnected",
                                godot::Callable( this, "_peer_disconnected" ) );

    get_multiplayer()->connect( "connected_to_server",
                                godot::Callable( this, "_client_connected_to_server" ) );
    get_multiplayer()->connect( "connection_failed",
                                godot::Callable( this, "_client_connection_failed" ) );
    get_multiplayer()->connect( "server_disconnected",
                                godot::Callable( this, "_client_server_disconnected" ) );
}

godot::Error CollaborationSession::start_server() {
    auto err = local_peer->enet_peer->create_server( 12345 );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to start listening." );

    return godot::OK;
}

godot::Error CollaborationSession::connect_to_server( const godot::String &p_address, int p_port ) {
    auto err = local_peer->enet_peer->create_client( p_address, p_port );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to attempt server connection." );

    return godot::OK;
}

void CollaborationSession::add_local_avatar( Avatar *p_avatar ) {
    ERR_FAIL_COND_MSG( local_avatars.has( p_avatar ),
                       "Local avatar is already joined to the session." );

    // Set the node's multiplayer peer to the local peer.
    auto multi = p_avatar->get_multiplayer();
    multi->set_multiplayer_peer( local_peer );

    local_avatars.push_back( p_avatar );
    emit_signal( "local_avatar_added", p_avatar );
}

void CollaborationSession::remove_local_avatar( Avatar *p_avatar ) {
    ERR_FAIL_COND_MSG( local_avatars.has( p_avatar ),
                       "Local avatar hasn't been added to the session." );

    auto index = local_avatars.find( p_avatar );
    local_avatars.remove_at( index );
    emit_signal( "local_avatar_removed", p_avatar );
}

void CollaborationSession::_client_connected_to_server() {
    godot::UtilityFunctions::print( "Client connected to server" );
}

void CollaborationSession::_client_connection_failed() {
    godot::UtilityFunctions::print( "Client connection failed" );
}

void CollaborationSession::_client_server_disconnected() {
    godot::UtilityFunctions::print( "Client server disconnected" );
}

void CollaborationSession::_peer_connected( int id ) {
    auto peer = local_peer->enet_peer->get_peer( id );
    godot::Ref<CollaborationPeer> collab_peer = memnew( CollaborationPeer( peer ) );
    remote_peers[id] = collab_peer;

    emit_signal( "peer_connected", collab_peer );
}

void CollaborationSession::_peer_disconnected( int id ) {
    auto peer = local_peer->enet_peer->get_peer( id );

    emit_signal( "peer_disconnected", remote_peers[id] );

    remote_peers.erase( id );
}
