

#ifndef VDOT_VTS_CLIENT_H
#define VDOT_VTS_CLIENT_H

#include <godot_cpp/classes/packet_peer_udp.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "../../standards/arkit_blend_shapes.h"

/**
 * Container for decoded VTS face tracking data.
 */
class VTSData : public godot::RefCounted {
    GDCLASS( VTSData, godot::RefCounted )

    godot::Dictionary _empty_vec3;

  protected:
    static void _bind_methods();

  public:
    uint64_t timestamp;

    // indicates if an on-screen hotkey in the mobile app was pressed.
    int hotkey = -1;

    // indicates if there is a face visible to the camera that's being tracked
    bool face_found = false;

    godot::Vector3 head_position;
    godot::Vector3 head_rotation;
    godot::Vector3 eye_rotation_left;
    godot::Vector3 eye_rotation_right;

    // VTS uses ARKit blend shape names.
    float weights[ARKit::BlendShape::Max] = {};

    VTSData();
    ~VTSData() override;

    godot::Error decode_packet( const godot::PackedByteArray &packet );
};

/**
 * Wraps a UDP client connection to a VTS UDP server running on a mobile device.
 *
 * While this is typically the VTubeStudio app on iPhone, some other apps, such
 * as MeowFace on Android, use the same protocol so that cannot be assumed.
 */
class VTSClient : public godot::RefCounted {
    GDCLASS( VTSClient, godot::RefCounted )

    godot::Ref<VTSData> _data = nullptr;

    godot::String _address;
    int32_t _port = 21412;

    // cache the request packet since we send the same one repeatedly.
    godot::PackedByteArray _request_packet;

    godot::PacketPeerUDP *_client = nullptr;

  protected:
    static void _bind_methods();

  public:
    VTSClient();
    ~VTSClient() override;

    godot::Error connect();
    void disconnect();

    godot::Error receive();
};

#endif // VDOT_VTS_CLIENT_H
