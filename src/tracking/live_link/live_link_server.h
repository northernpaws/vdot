

#ifndef VDOT_LIVE_LINK_SERVER_H
#define VDOT_LIVE_LINK_SERVER_H

#include <cstdint>
#include <map>

#include "godot_cpp/classes/node.hpp"

#include "godot_cpp/classes/mutex.hpp"
#include "godot_cpp/classes/packet_peer_udp.hpp"
#include "godot_cpp/classes/thread.hpp"
#include "godot_cpp/classes/udp_server.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"

#include "../arkit/blend_shapes.h"

static constexpr int BLEND_SHAPE_COUNT = 61;

struct LiveLinkPacket {
    uint8_t magic_1;
    godot::String device_id;
    godot::String device_name;
    uint64_t time_stamp;
    uint64_t magic_2;

    godot::PackedFloat32Array blend_shapes;

    static LiveLinkPacket from_bytes( const godot::PackedByteArray &bytes );
};

/**
 * Holds and decodes packet data received from a Live Link client.
 */
class LiveLinkClientData : public godot::Object {
    GDCLASS( LiveLinkClientData, godot::Object )
  protected:
    static void _bind_methods();

  public:
    enum DataIndex {
        BlendShapeCount = 0,

        // ARKit Blendshapes

        EyeBlinkLeft = 1,
        EyeLookDownLeft = 2,
        EyeLookInLeft = 3,
        EyeLookOutLeft = 4,
        EyeLookUpLeft = 5,
        EyeSquintLeft = 6,
        EyeWideLeft = 7,

        EyeBlinkRight = 8,
        EyeLookDownRight = 9,
        EyeLookInRight = 10,
        EyeLookOutRight = 11,
        EyeLookUpRight = 12,
        EyeSquintRight = 13,
        EyeWideRight = 14,

        JawForward = 15,
        JawRight = 16,
        JawLeft = 17,
        JawOpen = 18,

        MouthClose = 19,
        MouthFunnel = 20,
        MouthPucker = 21,
        MouthRight = 22,
        MouthLeft = 23,

        MouthSmileLeft = 24,
        MouthSmileRight = 25,

        MouthFrownLeft = 26,
        MouthFrownRight = 27,

        MouthDimpleLeft = 28,
        MouthDimpleRight = 29,

        MouthStretchLeft = 30,
        MouthStretchRight = 31,

        MouthRollLower = 32,
        MouthRollUpper = 33,
        MouthShrugLower = 34,
        MouthShrugUpper = 35,

        MouthPressLeft = 36,
        MouthPressRight = 37,

        MouthLowerDownLeft = 38,
        MouthLowerDownRight = 39,

        MouthUpperUpLeft = 40,
        MouthUpperUpRight = 41,

        BrowDownLeft = 42,
        BrowDownRight = 43,

        BrowInnerUp = 44,

        BrowOuterUpLeft = 45,
        BrowOuterUpRight = 46,

        CheekPuff = 47,

        CheekSquintLeft = 48,
        CheekSquintRight = 49,

        NoseSneerLeft = 50,
        NoseSneerRight = 51,

        TongueOut = 52,

        // LiveLink specific
        HeadYaw = 53,
        HeadPitch = 54,
        HeadRoll = 55,

        LeftEyeYaw = 56,
        LeftEyePitch = 57,
        LeftEyeRoll = 58,

        RightEyeYaw = 59,
        RightEyePitch = 60,
        RightEyeRoll = 61,
    };

    uint64_t _timecode;
    godot::PackedFloat32Array _data;

    LiveLinkClientData();
    ~LiveLinkClientData() override;

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

VARIANT_ENUM_CAST( LiveLinkClientData::DataIndex );

/**
 * Represents a client device connected to the Live Link server.
 *
 * Contains information about the connected client, and the client's current blend-shape values.
 */
class LiveLinkClient : public godot::Object {
    GDCLASS( LiveLinkClient, godot::Object )
  protected:
    static void _bind_methods();

  public:
    godot::String _id;
    godot::String _name;

    uint64_t _last_seen;
    godot::Ref<godot::PacketPeerUDP> _connection;

    LiveLinkClientData *_values; // tODO: use ref?

    LiveLinkClient();
    ~LiveLinkClient();
};

/**
 * Serves a Live Link server on the specified port that the Live Link Face app can connect to.
 */
class LiveLinkServer : public godot::Node {
    GDCLASS( LiveLinkServer, godot::Node )

    using PeerList = godot::List<godot::Ref<godot::PacketPeerUDP>>;

    uint16_t _port = 11111;

    godot::UDPServer *_server;
    godot::Mutex _server_mutex;
    bool _running = true;

    PeerList _unidentified_clients;
    std::map<godot::String, LiveLinkClient *> _clients;

    godot::Thread *_thread; // tODO: ref?
  protected:
    static void _bind_methods();

  public:
    bool _disable_polling = false;

    LiveLinkServer();
    ~LiveLinkServer() override;

    void _ready() override;

    void _process( double delta ) override;

    void _exit_tree() override;

    godot::Error listen();
    godot::Error stop();

    godot::Error poll();

    int get_port() const;
    void set_port( int port );

    void _thread_poll();
};

#endif // VDOT_LIVE_LINK_SERVER_H
