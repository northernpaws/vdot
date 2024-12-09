

#ifndef VDOT_LIVE_LINK_SERVER_H
#define VDOT_LIVE_LINK_SERVER_H

#include <cstdint>
#include <map>

#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/packet_peer_udp.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/udp_server.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

#include "../../standards/arkit_blend_shapes.h"

static constexpr int BLEND_SHAPE_COUNT = 61;

struct MeowFacePacket {
    uint8_t magic_1;
    godot::String device_id;
    godot::String device_name;
    uint64_t time_stamp;
    uint64_t magic_2;

    godot::PackedFloat32Array blend_shapes;

    static MeowFacePacket from_bytes( const godot::PackedByteArray &bytes );
};

/**
 * Holds and decodes packet data received from a Live Link client.
 */
class MeowFaceClientData : public godot::Object {
    GDCLASS( MeowFaceClientData, godot::Object )
  protected:
    static void _bind_methods();

  public:
    enum DataIndex {
        BlendShapeCount = 0,

        // ARKit Blendshapes

        EyeBlinkLeft = 0,
        EyeLookDownLeft = 1,
        EyeLookInLeft = 2,
        EyeLookOutLeft = 3,
        EyeLookUpLeft = 4,
        EyeSquintLeft = 5,
        EyeWideLeft = 6,

        EyeBlinkRight = 7,
        EyeLookDownRight = 8,
        EyeLookInRight = 9,
        EyeLookOutRight = 10,
        EyeLookUpRight = 11,
        EyeSquintRight = 12,
        EyeWideRight = 13,

        JawForward = 14,
        JawRight = 15,
        JawLeft = 16,
        JawOpen = 17,

        MouthClose = 18,
        MouthFunnel = 19,
        MouthPucker = 20,
        MouthRight = 21,
        MouthLeft = 22,

        MouthSmileLeft = 23,
        MouthSmileRight = 24,

        MouthFrownLeft = 25,
        MouthFrownRight = 26,

        MouthDimpleLeft = 27,
        MouthDimpleRight = 28,

        MouthStretchLeft = 29,
        MouthStretchRight = 30,

        MouthRollLower = 31,
        MouthRollUpper = 32,
        MouthShrugLower = 33,
        MouthShrugUpper = 34,

        MouthPressLeft = 35,
        MouthPressRight = 36,

        MouthLowerDownLeft = 37,
        MouthLowerDownRight = 38,

        MouthUpperUpLeft = 39,
        MouthUpperUpRight = 40,

        BrowDownLeft = 41,
        BrowDownRight = 42,

        BrowInnerUp = 43,

        BrowOuterUpLeft = 44,
        BrowOuterUpRight = 45,

        CheekPuff = 46,

        CheekSquintLeft = 47,
        CheekSquintRight = 48,

        NoseSneerLeft = 49,
        NoseSneerRight = 50,

        TongueOut = 51,

        // MeowFace specific
        HeadYaw = 52,
        HeadPitch = 53,
        HeadRoll = 54,

        LeftEyeYaw = 55,
        LeftEyePitch = 56,
        LeftEyeRoll = 57,

        RightEyeYaw = 58,
        RightEyePitch = 59,
        RightEyeRoll = 60,
    };

    uint64_t _timecode;
    godot::PackedFloat32Array _data;

    MeowFaceClientData();
    ~MeowFaceClientData() override;

    float get_blend_shape( ARKit::BlendShape blendShape );

    [[nodiscard]] float _get_eye_blink_left() const;
    [[nodiscard]] float _get_eye_look_down_left() const;
    [[nodiscard]] float _get_eye_look_in_left() const;
    [[nodiscard]] float _get_eye_look_out_left() const;
    [[nodiscard]] float _get_eye_look_up_left() const;
    [[nodiscard]] float _get_eye_squint_left() const;
    [[nodiscard]] float _get_eye_wide_left() const;
    [[nodiscard]] float _get_eye_blink_right() const;
    [[nodiscard]] float _get_eye_look_down_right() const;
    [[nodiscard]] float _get_eye_look_in_right() const;
    [[nodiscard]] float _get_eye_look_out_right() const;
    [[nodiscard]] float _get_eye_look_up_right() const;
    [[nodiscard]] float _get_eye_squint_right() const;
    [[nodiscard]] float _get_eye_wide_right() const;
    [[nodiscard]] float _get_jaw_forward() const;
    [[nodiscard]] float _get_jaw_right() const;
    [[nodiscard]] float _get_jaw_left() const;
    [[nodiscard]] float _get_jaw_open() const;
    [[nodiscard]] float _get_mouth_close() const;
    [[nodiscard]] float _get_mouth_funnel() const;
    [[nodiscard]] float _get_mouth_pucker() const;
    [[nodiscard]] float _get_mouth_right() const;
    [[nodiscard]] float _get_mouth_left() const;
    [[nodiscard]] float _get_mouth_smile_left() const;
    [[nodiscard]] float _get_mouth_smile_right() const;
    [[nodiscard]] float _get_mouth_frown_left() const;
    [[nodiscard]] float _get_mouth_frown_right() const;
    [[nodiscard]] float _get_mouth_dimple_left() const;
    [[nodiscard]] float _get_mouth_dimple_right() const;
    [[nodiscard]] float _get_mouth_stretch_left() const;
    [[nodiscard]] float _get_mouth_stretch_right() const;
    [[nodiscard]] float _get_mouth_roll_lower() const;
    [[nodiscard]] float _get_mouth_roll_upper() const;
    [[nodiscard]] float _get_mouth_shrug_lower() const;
    [[nodiscard]] float _get_mouth_shrug_upper() const;
    [[nodiscard]] float _get_mouth_press_left() const;
    [[nodiscard]] float _get_mouth_press_right() const;
    [[nodiscard]] float _get_mouth_lower_down_left() const;
    [[nodiscard]] float _get_mouth_lower_down_right() const;
    [[nodiscard]] float _get_mouth_upper_up_left() const;
    [[nodiscard]] float _get_mouth_upper_up_right() const;
    [[nodiscard]] float _get_brow_down_left() const;
    [[nodiscard]] float _get_brow_down_right() const;
    [[nodiscard]] float _get_brow_inner_up() const;
    [[nodiscard]] float _get_brow_outer_up_left() const;
    [[nodiscard]] float _get_brow_outer_up_right() const;
    [[nodiscard]] float _get_cheek_puff() const;
    [[nodiscard]] float _get_cheek_squint_left() const;
    [[nodiscard]] float _get_cheek_squint_right() const;
    [[nodiscard]] float _get_nose_sneer_left() const;
    [[nodiscard]] float _get_nose_sneer_right() const;
    [[nodiscard]] float _get_tongue_out() const;
    [[nodiscard]] float _get_head_yaw() const;
    [[nodiscard]] float _get_head_pitch() const;
    [[nodiscard]] float _get_head_roll() const;
    [[nodiscard]] float _get_left_eye_yaw() const;
    [[nodiscard]] float _get_left_eye_pitch() const;
    [[nodiscard]] float _get_left_eye_roll() const;
    [[nodiscard]] float _get_right_eye_yaw() const;
    [[nodiscard]] float _get_right_eye_pitch() const;
    [[nodiscard]] float _get_right_eye_roll() const;
};

VARIANT_ENUM_CAST( MeowFaceClientData::DataIndex );

/**
 * Represents a client device connected to the Live Link server.
 *
 * Contains information about the connected client, and the client's current blend-shape values.
 */
class MeowFaceClient : public godot::RefCounted {
    GDCLASS( MeowFaceClient, godot::RefCounted )
  protected:
    static void _bind_methods();

  public:
    godot::String _id;
    godot::String _name;

    uint64_t _last_seen;
    godot::Ref<godot::PacketPeerUDP> _connection;

    MeowFaceClientData *_values; // tODO: use ref?

    MeowFaceClient();
    ~MeowFaceClient();
};

/**
 * Serves a Live Link server on the specified port that the Live Link Face app can connect to.
 */
class MeowFaceServer : public godot::RefCounted {
    GDCLASS( MeowFaceServer, godot::RefCounted )

    using PeerList = godot::List<godot::Ref<godot::PacketPeerUDP>>;

    uint16_t _port = 11111;

    godot::UDPServer *_server = nullptr;
    godot::Mutex *_server_mutex = nullptr;
    bool _running = true;

    PeerList _unidentified_clients;
    // TODO: replace std map with godot VMap or vector?
    std::map<godot::String, godot::Ref<MeowFaceClient>> _clients;

    godot::Thread *_thread; // tODO: ref?
  protected:
    static void _bind_methods();

  public:
    bool _disable_polling = false;

    MeowFaceServer();
    ~MeowFaceServer() override;

    godot::Error listen();
    godot::Error stop();

    godot::Error poll();

    [[nodiscard]] uint16_t get_port() const;
    void set_port( uint16_t port );

    void _thread_poll();
};

#endif // VDOT_LIVE_LINK_SERVER_H
