#include "godot_cpp/classes/class_db_singleton.hpp"
#include "godot_cpp/classes/stream_peer_buffer.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

#include "live_link_server.h"

LiveLinkPacket LiveLinkPacket::from_bytes( const godot::PackedByteArray &bytes ) {
    auto stream = memnew( godot::StreamPeerBuffer() );
    stream->set_data_array( bytes );
    stream->set_big_endian( true );

    auto packet = LiveLinkPacket();

    packet.magic_1 = stream->get_u8();
    packet.device_id = stream->get_string();
    packet.device_name = stream->get_string();
    packet.time_stamp = stream->get_u64();
    packet.magic_2 = stream->get_u64();

    if ( ( stream->get_size() - stream->get_position() ) > 0 ) {
        auto blend_shape_count = stream->get_u8();
        godot::Array blend_shapes;

        for ( int i = 0; i < blend_shape_count; ++i ) {
            blend_shapes.append( stream->get_float() );
        }

        packet.blend_shapes = godot::PackedFloat32Array( blend_shapes );
    }

    return packet;
}

void LiveLinkClientData::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_blink_left" ),
                                 &LiveLinkClientData::_get_eye_blink_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_blink_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_blink_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_down_left" ),
                                 &LiveLinkClientData::_get_eye_look_down_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_down_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_down_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_in_left" ),
                                 &LiveLinkClientData::_get_eye_look_in_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_in_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_in_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_out_left" ),
                                 &LiveLinkClientData::_get_eye_look_out_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_out_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_out_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_up_left" ),
                                 &LiveLinkClientData::_get_eye_look_up_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_up_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_up_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_squint_left" ),
                                 &LiveLinkClientData::_get_eye_squint_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_squint_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_squint_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_wide_left" ),
                                 &LiveLinkClientData::_get_eye_wide_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_wide_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_wide_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_blink_right" ),
                                 &LiveLinkClientData::_get_eye_blink_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_blink_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_blink_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_down_right" ),
                                 &LiveLinkClientData::_get_eye_look_down_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_down_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_down_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_in_right" ),
                                 &LiveLinkClientData::_get_eye_look_in_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_in_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_in_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_out_right" ),
                                 &LiveLinkClientData::_get_eye_look_out_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_out_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_out_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_look_up_right" ),
                                 &LiveLinkClientData::_get_eye_look_up_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_look_up_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_look_up_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_squint_right" ),
                                 &LiveLinkClientData::_get_eye_squint_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_squint_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_squint_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_eye_wide_right" ),
                                 &LiveLinkClientData::_get_eye_wide_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eye_wide_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_eye_wide_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_jaw_forward" ),
                                 &LiveLinkClientData::_get_jaw_forward );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "jaw_forward",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_jaw_forward" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_jaw_right" ),
                                 &LiveLinkClientData::_get_jaw_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "jaw_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_jaw_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_jaw_left" ),
                                 &LiveLinkClientData::_get_jaw_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "jaw_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_jaw_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_jaw_open" ),
                                 &LiveLinkClientData::_get_jaw_open );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "jaw_open",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_jaw_open" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_close" ),
                                 &LiveLinkClientData::_get_mouth_close );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_close",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_close" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_funnel" ),
                                 &LiveLinkClientData::_get_mouth_funnel );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_funnel",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_funnel" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_pucker" ),
                                 &LiveLinkClientData::_get_mouth_pucker );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_pucker",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_pucker" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_right" ),
                                 &LiveLinkClientData::_get_mouth_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_left" ),
                                 &LiveLinkClientData::_get_mouth_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_smile_left" ),
                                 &LiveLinkClientData::_get_mouth_smile_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_smile_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_smile_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_smile_right" ),
                                 &LiveLinkClientData::_get_mouth_smile_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_smile_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_smile_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_frown_left" ),
                                 &LiveLinkClientData::_get_mouth_frown_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_frown_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_frown_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_frown_right" ),
                                 &LiveLinkClientData::_get_mouth_frown_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_frown_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_frown_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_dimple_left" ),
                                 &LiveLinkClientData::_get_mouth_dimple_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_dimple_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_dimple_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_dimple_right" ),
                                 &LiveLinkClientData::_get_mouth_dimple_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_dimple_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_dimple_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_stretch_left" ),
                                 &LiveLinkClientData::_get_mouth_stretch_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_stretch_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_stretch_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_stretch_right" ),
                                 &LiveLinkClientData::_get_mouth_stretch_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_stretch_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_stretch_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_roll_lower" ),
                                 &LiveLinkClientData::_get_mouth_roll_lower );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_roll_lower",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_roll_lower" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_roll_upper" ),
                                 &LiveLinkClientData::_get_mouth_roll_upper );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_roll_upper",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_roll_upper" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_shrug_lower" ),
                                 &LiveLinkClientData::_get_mouth_shrug_lower );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_shrug_lower",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_shrug_lower" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_shrug_upper" ),
                                 &LiveLinkClientData::_get_mouth_shrug_upper );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_shrug_upper",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_shrug_upper" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_press_left" ),
                                 &LiveLinkClientData::_get_mouth_press_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_press_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_press_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_press_right" ),
                                 &LiveLinkClientData::_get_mouth_press_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_press_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_press_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_lower_down_left" ),
                                 &LiveLinkClientData::_get_mouth_lower_down_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_lower_down_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_lower_down_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_lower_down_right" ),
                                 &LiveLinkClientData::_get_mouth_lower_down_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_lower_down_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_lower_down_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_upper_up_left" ),
                                 &LiveLinkClientData::_get_mouth_upper_up_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_upper_up_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_upper_up_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_mouth_upper_up_right" ),
                                 &LiveLinkClientData::_get_mouth_upper_up_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "mouth_upper_up_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_mouth_upper_up_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_brow_down_left" ),
                                 &LiveLinkClientData::_get_brow_down_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "brow_down_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_brow_down_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_brow_down_right" ),
                                 &LiveLinkClientData::_get_brow_down_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "brow_down_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_brow_down_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_brow_inner_up" ),
                                 &LiveLinkClientData::_get_brow_inner_up );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "brow_inner_up",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_brow_inner_up" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_brow_outer_up_left" ),
                                 &LiveLinkClientData::_get_brow_outer_up_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "brow_outer_up_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_brow_outer_up_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_brow_outer_up_right" ),
                                 &LiveLinkClientData::_get_brow_outer_up_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "brow_outer_up_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_brow_outer_up_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_cheek_puff" ),
                                 &LiveLinkClientData::_get_cheek_puff );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "cheek_puff",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_cheek_puff" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_cheek_squint_left" ),
                                 &LiveLinkClientData::_get_cheek_squint_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "cheek_squint_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_cheek_squint_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_cheek_squint_right" ),
                                 &LiveLinkClientData::_get_cheek_squint_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "cheek_squint_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_cheek_squint_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_nose_sneer_left" ),
                                 &LiveLinkClientData::_get_nose_sneer_left );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "nose_sneer_left",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_nose_sneer_left" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_nose_sneer_right" ),
                                 &LiveLinkClientData::_get_nose_sneer_right );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "nose_sneer_right",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_nose_sneer_right" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_tongue_out" ),
                                 &LiveLinkClientData::_get_tongue_out );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "tongue_out",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_tongue_out" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_head_yaw" ),
                                 &LiveLinkClientData::_get_head_yaw );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "head_yaw",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_head_yaw" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_head_pitch" ),
                                 &LiveLinkClientData::_get_head_pitch );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "head_pitch",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_head_pitch" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_head_roll" ),
                                 &LiveLinkClientData::_get_head_roll );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "head_roll",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_head_roll" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_left_eye_yaw" ),
                                 &LiveLinkClientData::_get_left_eye_yaw );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "left_eye_yaw",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_left_eye_yaw" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_left_eye_pitch" ),
                                 &LiveLinkClientData::_get_left_eye_pitch );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "left_eye_pitch",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_left_eye_pitch" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_left_eye_roll" ),
                                 &LiveLinkClientData::_get_left_eye_roll );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "left_eye_roll",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_left_eye_roll" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_right_eye_yaw" ),
                                 &LiveLinkClientData::_get_right_eye_yaw );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "right_eye_yaw",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_right_eye_yaw" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_right_eye_pitch" ),
                                 &LiveLinkClientData::_get_right_eye_pitch );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "right_eye_pitch",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_right_eye_pitch" );
    godot::ClassDB::bind_method( godot::D_METHOD( "_get_right_eye_roll" ),
                                 &LiveLinkClientData::_get_right_eye_roll );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "right_eye_roll",
                                       godot::PropertyHint::PROPERTY_HINT_NONE, "",
                                       godot::PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY ),
                  "", "_get_right_eye_roll" );

    BIND_ENUM_CONSTANT( DataIndex::EyeBlinkLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookDownLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookInLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookOutLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookUpLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeSquintLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeWideLeft )
    BIND_ENUM_CONSTANT( DataIndex::EyeBlinkRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookDownRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookInRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookOutRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeLookUpRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeSquintRight )
    BIND_ENUM_CONSTANT( DataIndex::EyeWideRight )
    BIND_ENUM_CONSTANT( DataIndex::JawForward )
    BIND_ENUM_CONSTANT( DataIndex::JawRight )
    BIND_ENUM_CONSTANT( DataIndex::JawLeft )
    BIND_ENUM_CONSTANT( DataIndex::JawOpen )
    BIND_ENUM_CONSTANT( DataIndex::MouthClose )
    BIND_ENUM_CONSTANT( DataIndex::MouthFunnel )
    BIND_ENUM_CONSTANT( DataIndex::MouthPucker )
    BIND_ENUM_CONSTANT( DataIndex::MouthRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthSmileLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthSmileRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthFrownLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthFrownRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthDimpleLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthDimpleRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthStretchLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthStretchRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthRollLower )
    BIND_ENUM_CONSTANT( DataIndex::MouthRollUpper )
    BIND_ENUM_CONSTANT( DataIndex::MouthShrugLower )
    BIND_ENUM_CONSTANT( DataIndex::MouthShrugUpper )
    BIND_ENUM_CONSTANT( DataIndex::MouthPressLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthPressRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthLowerDownLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthLowerDownRight )
    BIND_ENUM_CONSTANT( DataIndex::MouthUpperUpLeft )
    BIND_ENUM_CONSTANT( DataIndex::MouthUpperUpRight )
    BIND_ENUM_CONSTANT( DataIndex::BrowDownLeft )
    BIND_ENUM_CONSTANT( DataIndex::BrowDownRight )
    BIND_ENUM_CONSTANT( DataIndex::BrowInnerUp )
    BIND_ENUM_CONSTANT( DataIndex::BrowOuterUpLeft )
    BIND_ENUM_CONSTANT( DataIndex::BrowOuterUpRight )
    BIND_ENUM_CONSTANT( DataIndex::CheekPuff )
    BIND_ENUM_CONSTANT( DataIndex::CheekSquintLeft )
    BIND_ENUM_CONSTANT( DataIndex::CheekSquintRight )
    BIND_ENUM_CONSTANT( DataIndex::NoseSneerLeft )
    BIND_ENUM_CONSTANT( DataIndex::NoseSneerRight )
    BIND_ENUM_CONSTANT( DataIndex::TongueOut )
    BIND_ENUM_CONSTANT( DataIndex::HeadYaw )
    BIND_ENUM_CONSTANT( DataIndex::HeadPitch )
    BIND_ENUM_CONSTANT( DataIndex::HeadRoll )
    BIND_ENUM_CONSTANT( DataIndex::LeftEyeYaw )
    BIND_ENUM_CONSTANT( DataIndex::LeftEyePitch )
    BIND_ENUM_CONSTANT( DataIndex::LeftEyeRoll )
    BIND_ENUM_CONSTANT( DataIndex::RightEyeYaw )
    BIND_ENUM_CONSTANT( DataIndex::RightEyePitch )
    BIND_ENUM_CONSTANT( DataIndex::RightEyeRoll )

    BIND_ENUM_CONSTANT( ARKit::EyeBlinkLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeLookDownLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeLookInLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeLookOutLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeLookUpLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeSquintLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeWideLeft )
    BIND_ENUM_CONSTANT( ARKit::EyeBlinkRight )
    BIND_ENUM_CONSTANT( ARKit::EyeLookDownRight )
    BIND_ENUM_CONSTANT( ARKit::EyeLookInRight )
    BIND_ENUM_CONSTANT( ARKit::EyeLookOutRight )
    BIND_ENUM_CONSTANT( ARKit::EyeLookUpRight )
    BIND_ENUM_CONSTANT( ARKit::EyeSquintRight )
    BIND_ENUM_CONSTANT( ARKit::EyeWideRight )
    BIND_ENUM_CONSTANT( ARKit::JawForward )
    BIND_ENUM_CONSTANT( ARKit::JawRight )
    BIND_ENUM_CONSTANT( ARKit::JawLeft )
    BIND_ENUM_CONSTANT( ARKit::JawOpen )
    BIND_ENUM_CONSTANT( ARKit::MouthClose )
    BIND_ENUM_CONSTANT( ARKit::MouthFunnel )
    BIND_ENUM_CONSTANT( ARKit::MouthPucker )
    BIND_ENUM_CONSTANT( ARKit::MouthRight )
    BIND_ENUM_CONSTANT( ARKit::MouthLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthSmileLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthSmileRight )
    BIND_ENUM_CONSTANT( ARKit::MouthFrownLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthFrownRight )
    BIND_ENUM_CONSTANT( ARKit::MouthDimpleLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthDimpleRight )
    BIND_ENUM_CONSTANT( ARKit::MouthStretchLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthStretchRight )
    BIND_ENUM_CONSTANT( ARKit::MouthRollLower )
    BIND_ENUM_CONSTANT( ARKit::MouthRollUpper )
    BIND_ENUM_CONSTANT( ARKit::MouthShrugLower )
    BIND_ENUM_CONSTANT( ARKit::MouthShrugUpper )
    BIND_ENUM_CONSTANT( ARKit::MouthPressLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthPressRight )
    BIND_ENUM_CONSTANT( ARKit::MouthLowerDownLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthLowerDownRight )
    BIND_ENUM_CONSTANT( ARKit::MouthUpperUpLeft )
    BIND_ENUM_CONSTANT( ARKit::MouthUpperUpRight )
    BIND_ENUM_CONSTANT( ARKit::BrowDownLeft )
    BIND_ENUM_CONSTANT( ARKit::BrowDownRight )
    BIND_ENUM_CONSTANT( ARKit::BrowInnerUp )
    BIND_ENUM_CONSTANT( ARKit::BrowOuterUpLeft )
    BIND_ENUM_CONSTANT( ARKit::BrowOuterUpRight )
    BIND_ENUM_CONSTANT( ARKit::CheekPuff )
    BIND_ENUM_CONSTANT( ARKit::CheekSquintLeft )
    BIND_ENUM_CONSTANT( ARKit::CheekSquintRight )
    BIND_ENUM_CONSTANT( ARKit::NoseSneerLeft )
    BIND_ENUM_CONSTANT( ARKit::NoseSneerRight )
    BIND_ENUM_CONSTANT( ARKit::TongueOut )
}

LiveLinkClientData::LiveLinkClientData() {
}

LiveLinkClientData::~LiveLinkClientData() {
}

float LiveLinkClientData::get_blend_shape( ARKit::BlendShape blendShape ) {
    // +1 because the LiveLink data uses 0 as a blend shape count index.
    // TODO: double check the +1 reasoning
    return _data[blendShape+1];
}

float LiveLinkClientData::_get_eye_blink_left() const {
    return _data[DataIndex::EyeBlinkLeft];
}

float LiveLinkClientData::_get_eye_look_down_left() const {
    return _data[DataIndex::EyeLookDownLeft];
}

float LiveLinkClientData::_get_eye_look_in_left() const {
    return _data[DataIndex::EyeLookInLeft];
}

float LiveLinkClientData::_get_eye_look_out_left() const {
    return _data[DataIndex::EyeLookOutLeft];
}

float LiveLinkClientData::_get_eye_look_up_left() const {
    return _data[DataIndex::EyeLookUpLeft];
}

float LiveLinkClientData::_get_eye_squint_left() const {
    return _data[DataIndex::EyeSquintLeft];
}

float LiveLinkClientData::_get_eye_wide_left() const {
    return _data[DataIndex::EyeWideLeft];
}

float LiveLinkClientData::_get_eye_blink_right() const {
    return _data[DataIndex::EyeBlinkRight];
}

float LiveLinkClientData::_get_eye_look_down_right() const {
    return _data[DataIndex::EyeLookDownRight];
}

float LiveLinkClientData::_get_eye_look_in_right() const {
    return _data[DataIndex::EyeLookInRight];
}

float LiveLinkClientData::_get_eye_look_out_right() const {
    return _data[DataIndex::EyeLookOutRight];
}

float LiveLinkClientData::_get_eye_look_up_right() const {
    return _data[DataIndex::EyeLookUpRight];
}

float LiveLinkClientData::_get_eye_squint_right() const {
    return _data[DataIndex::EyeSquintRight];
}

float LiveLinkClientData::_get_eye_wide_right() const {
    return _data[DataIndex::EyeWideRight];
}

float LiveLinkClientData::_get_jaw_forward() const {
    return _data[DataIndex::JawForward];
}

float LiveLinkClientData::_get_jaw_right() const {
    return _data[DataIndex::JawRight];
}

float LiveLinkClientData::_get_jaw_left() const {
    return _data[DataIndex::JawLeft];
}

float LiveLinkClientData::_get_jaw_open() const {
    return _data[DataIndex::JawOpen];
}

float LiveLinkClientData::_get_mouth_close() const {
    return _data[DataIndex::MouthClose];
}

float LiveLinkClientData::_get_mouth_funnel() const {
    return _data[DataIndex::MouthFunnel];
}

float LiveLinkClientData::_get_mouth_pucker() const {
    return _data[DataIndex::MouthPucker];
}

float LiveLinkClientData::_get_mouth_right() const {
    return _data[DataIndex::MouthRight];
}

float LiveLinkClientData::_get_mouth_left() const {
    return _data[DataIndex::MouthLeft];
}

float LiveLinkClientData::_get_mouth_smile_left() const {
    return _data[DataIndex::MouthSmileLeft];
}

float LiveLinkClientData::_get_mouth_smile_right() const {
    return _data[DataIndex::MouthSmileRight];
}

float LiveLinkClientData::_get_mouth_frown_left() const {
    return _data[DataIndex::MouthFrownLeft];
}

float LiveLinkClientData::_get_mouth_frown_right() const {
    return _data[DataIndex::MouthFrownRight];
}

float LiveLinkClientData::_get_mouth_dimple_left() const {
    return _data[DataIndex::MouthDimpleLeft];
}

float LiveLinkClientData::_get_mouth_dimple_right() const {
    return _data[DataIndex::MouthDimpleRight];
}

float LiveLinkClientData::_get_mouth_stretch_left() const {
    return _data[DataIndex::MouthStretchLeft];
}

float LiveLinkClientData::_get_mouth_stretch_right() const {
    return _data[DataIndex::MouthStretchRight];
}

float LiveLinkClientData::_get_mouth_roll_lower() const {
    return _data[DataIndex::MouthRollLower];
}

float LiveLinkClientData::_get_mouth_roll_upper() const {
    return _data[DataIndex::MouthRollUpper];
}

float LiveLinkClientData::_get_mouth_shrug_lower() const {
    return _data[DataIndex::MouthShrugLower];
}

float LiveLinkClientData::_get_mouth_shrug_upper() const {
    return _data[DataIndex::MouthShrugUpper];
}

float LiveLinkClientData::_get_mouth_press_left() const {
    return _data[DataIndex::MouthPressLeft];
}

float LiveLinkClientData::_get_mouth_press_right() const {
    return _data[DataIndex::MouthPressRight];
}

float LiveLinkClientData::_get_mouth_lower_down_left() const {
    return _data[DataIndex::MouthLowerDownLeft];
}

float LiveLinkClientData::_get_mouth_lower_down_right() const {
    return _data[DataIndex::MouthLowerDownRight];
}

float LiveLinkClientData::_get_mouth_upper_up_left() const {
    return _data[DataIndex::MouthUpperUpLeft];
}

float LiveLinkClientData::_get_mouth_upper_up_right() const {
    return _data[DataIndex::MouthUpperUpRight];
}

float LiveLinkClientData::_get_brow_down_left() const {
    return _data[DataIndex::BrowDownLeft];
}

float LiveLinkClientData::_get_brow_down_right() const {
    return _data[DataIndex::BrowDownRight];
}

float LiveLinkClientData::_get_brow_inner_up() const {
    return _data[DataIndex::BrowInnerUp];
}

float LiveLinkClientData::_get_brow_outer_up_left() const {
    return _data[DataIndex::BrowOuterUpLeft];
}

float LiveLinkClientData::_get_brow_outer_up_right() const {
    return _data[DataIndex::BrowOuterUpRight];
}

float LiveLinkClientData::_get_cheek_puff() const {
    return _data[DataIndex::CheekPuff];
}

float LiveLinkClientData::_get_cheek_squint_left() const {
    return _data[DataIndex::CheekSquintLeft];
}

float LiveLinkClientData::_get_cheek_squint_right() const {
    return _data[DataIndex::CheekSquintRight];
}

float LiveLinkClientData::_get_nose_sneer_left() const {
    return _data[DataIndex::NoseSneerLeft];
}

float LiveLinkClientData::_get_nose_sneer_right() const {
    return _data[DataIndex::NoseSneerRight];
}

float LiveLinkClientData::_get_tongue_out() const {
    return _data[DataIndex::TongueOut];
}

float LiveLinkClientData::_get_head_yaw() const {
    return _data[DataIndex::HeadYaw];
}

float LiveLinkClientData::_get_head_pitch() const {
    return _data[DataIndex::HeadPitch];
}

float LiveLinkClientData::_get_head_roll() const {
    return _data[DataIndex::HeadRoll];
}

float LiveLinkClientData::_get_left_eye_yaw() const {
    return _data[DataIndex::LeftEyeYaw];
}

float LiveLinkClientData::_get_left_eye_pitch() const {
    return _data[DataIndex::LeftEyePitch];
}

float LiveLinkClientData::_get_left_eye_roll() const {
    return _data[DataIndex::LeftEyeRoll];
}

float LiveLinkClientData::_get_right_eye_yaw() const {
    return _data[DataIndex::RightEyeYaw];
}

float LiveLinkClientData::_get_right_eye_pitch() const {
    return _data[DataIndex::RightEyePitch];
}

float LiveLinkClientData::_get_right_eye_roll() const {
    return _data[DataIndex::RightEyeRoll];
}

void LiveLinkClient::_bind_methods() {
}

LiveLinkClient::LiveLinkClient() {
}

LiveLinkClient::~LiveLinkClient() {
}

void LiveLinkServer::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "client_connected", godot::PropertyInfo( godot::Variant::OBJECT, "client",
                                                 godot::PropertyHint::PROPERTY_HINT_RESOURCE_TYPE,
                                                 LiveLinkClient::get_class_static() ) ) );
    ADD_SIGNAL(
        godot::MethodInfo( "client_disconnected",
                           godot::PropertyInfo( godot::Variant::OBJECT, "client",
                                                godot::PropertyHint::PROPERTY_HINT_RESOURCE_TYPE,
                                                LiveLinkClient::get_class_static() ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "client_updated", godot::PropertyInfo( godot::Variant::OBJECT, "client",
                                               godot::PropertyHint::PROPERTY_HINT_RESOURCE_TYPE,
                                               LiveLinkClient::get_class_static() ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_port" ), &LiveLinkServer::get_port );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_port", "port" ), &LiveLinkServer::set_port );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::INT, "port" ), "set_port", "get_port" );

    godot::ClassDB::bind_method( godot::D_METHOD( "listen" ), &LiveLinkServer::listen );
    godot::ClassDB::bind_method( godot::D_METHOD( "stop" ), &LiveLinkServer::stop );
    godot::ClassDB::bind_method( godot::D_METHOD( "poll" ), &LiveLinkServer::poll );

    godot::ClassDB::bind_method( godot::D_METHOD( "_thread_poll" ), &LiveLinkServer::_thread_poll );
}

LiveLinkServer::LiveLinkServer() {
    _server = memnew( godot::UDPServer );
    _server_mutex = memnew( godot::Mutex );
    _thread = memnew( godot::Thread() );
}

LiveLinkServer::~LiveLinkServer() {
    if ( !_disable_polling ) {
        // Thread must be disposed (or "joined"), for portability.
        _thread->wait_to_finish();
    }

    if ( _server ) {
        memdelete( _server );
    }

    memdelete( _server_mutex );
    memdelete( _thread );
}

godot::Error LiveLinkServer::listen() {
    if ( auto err = _server->listen( _port ); err != godot::OK ) {
        return err;
    }

    _running = true;
    if ( !_disable_polling ) {
        _thread->start( godot::Callable( this, "_thread_poll" ) );
    }

    godot::UtilityFunctions::print( "Started LiveLink server on: ", _port );

    return godot::OK;
}

godot::Error LiveLinkServer::stop() {
    _running = false;
    _server->stop();

    for ( const auto &item : _clients ) {
        godot::UtilityFunctions::print(
            "Existing LiveLinkFace peer disconnected for shutdown: %s (%s)", item.second->_name,
            item.second->_id );
        emit_signal( "client_disconnected", item.second );
    }

    _clients.clear();
    _unidentified_clients.clear();

    godot::UtilityFunctions::print( "Stopped LiveLink server on: ", _port );

    return godot::OK;
}

godot::Error LiveLinkServer::poll() {
    if ( auto err = _server->poll(); err != godot::OK ) {
        return err;
    }

    if ( _server->is_connection_available() ) {
        auto peer = _server->take_connection();

        if ( peer.is_valid() ) {
            _unidentified_clients.push_back( peer );
        }
    }

    godot::Array resolved_peers;
    for ( int peer_idx = 0; peer_idx < _unidentified_clients.size(); peer_idx++ ) {
        auto &peer = _unidentified_clients[peer_idx];

        auto packet_count = peer->get_available_packet_count();

        if ( packet_count <= 0 ) {
            break;
        }

        // Pop all but the latest packet.
        for ( int i = 0; i < packet_count - 1; ++i ) {
            auto p = peer->get_packet();
        }

        LiveLinkPacket packet = LiveLinkPacket::from_bytes( peer->get_packet() );

        if ( _clients.count( packet.device_id ) ) {
            // If there is already a connection registered for this device,
            // remove the connection and replace it with the new one.

            godot::Ref<LiveLinkClient> client = memnew( LiveLinkClient() );
            client->_connection->close();
            client->_connection = peer;
            _clients[packet.device_id] = client;
        } else {
            // Otherwise, create the new client for the connection.

            godot::Ref<LiveLinkClient> client = memnew( LiveLinkClient() );
            client->_connection = peer;
            client->_last_seen = packet.time_stamp;
            client->_id = packet.device_id;
            client->_name = packet.device_name;

            if ( packet.blend_shapes.size() == BLEND_SHAPE_COUNT ) {
                auto values = memnew( LiveLinkClientData() );
                values->_data = packet.blend_shapes;
                values->_timecode = packet.time_stamp;
                client->_values = values;
            }

            _clients[packet.device_id] = client;

            godot::UtilityFunctions::print( "New LiveLinkFace peer connected: %s (%s)",
                                            client->_name, client->_id );

            emit_signal( "client_connected", client );
        }

        resolved_peers.push_back( peer_idx );
    }

    // Clear unidentified peers that are now known.
    if ( _unidentified_clients.size() > 0 ) {
        PeerList temp_unidentified;
        for ( int peer_idx = 0; peer_idx < _unidentified_clients.size(); peer_idx++ ) {
            if ( resolved_peers.find( peer_idx ) == -1 ) {
                temp_unidentified.push_back( _unidentified_clients[peer_idx] );
            }
        }

        _unidentified_clients = temp_unidentified;
    }

    // Now poll for packets from clients with already established connections
    for ( const auto &item : _clients ) {
        auto client = item.second;
        auto packets_available = client->_connection->get_available_packet_count();

        if ( packets_available == 0 ) {
            continue;
        }

        // Discard all but the most recent packet
        for ( int i = 0; i < packets_available - 1; i++ ) {
            client->_connection->get_packet(); // discard
        }

        auto packet = LiveLinkPacket::from_bytes( client->_connection->get_packet() );

        client->_last_seen = packet.time_stamp;

        if ( packet.blend_shapes.size() == BLEND_SHAPE_COUNT ) {
            // TODO: should we be using recounted and creating a new instance instead?
            client->_values->_data = packet.blend_shapes;
            client->_values->_timecode = packet.time_stamp;

            emit_signal( "client_updated", client );
        }
    }

    return godot::OK;
}

uint16_t LiveLinkServer::get_port() const {
    return _port;
}

void LiveLinkServer::set_port( uint16_t port ) {
    _port = port;

    stop();
    listen();
}

void LiveLinkServer::_thread_poll() {
    while ( _running ) {
        if ( _server_mutex->try_lock() ) {
            poll();
            _server_mutex->unlock();
        }
    }
}