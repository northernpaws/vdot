

#ifndef VDOT_COLLABORATION_PEER_H
#define VDOT_COLLABORATION_PEER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>

#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>

/**
 * A common base-type for collaboration servers and
 *  clients that handles common events between them.
 */
class CollaborationPeer : public godot::RefCounted {
    GDCLASS( CollaborationPeer, godot::RefCounted )
  protected:

    static void _bind_methods();
  public:
    godot::Ref<godot::ENetMultiplayerPeer> enet_peer;

    CollaborationPeer();
    explicit CollaborationPeer(const godot::Ref<godot::ENetMultiplayerPeer>& p_peer);

    [[nodiscard]] godot::Ref<godot::ENetMultiplayerPeer> get_enet_peer() const;
};

#endif // VDOT_COLLABORATION_PEER_H
