

#include "collaboration_peer.h"

void CollaborationPeer::_bind_methods() {
}

CollaborationPeer::CollaborationPeer() {
}

CollaborationPeer::CollaborationPeer( const godot::Ref<godot::ENetMultiplayerPeer> &p_peer ) :
    enet_peer( p_peer ) {
}

godot::Ref<godot::ENetMultiplayerPeer> CollaborationPeer::get_enet_peer() const {
    return enet_peer;
}
