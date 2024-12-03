
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/base_material3d.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/environment.hpp>
#include <godot_cpp/classes/h_split_container.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/sub_viewport_container.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/world_environment.hpp>
#include <godot_cpp/classes/world3d.hpp>

#include "godot_cpp/variant/callable.hpp"
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "live_link_panel.h"

void LiveLinkPanel::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_start_button_pressed" ),
                                 &LiveLinkPanel::_on_start_button_pressed );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_connected" ),
                                 &LiveLinkPanel::_on_server_client_connected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_disconnected" ),
                                 &LiveLinkPanel::_on_server_client_disconnected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_updated" ),
                                 &LiveLinkPanel::_on_server_client_updated );
}

LiveLinkPanel::LiveLinkPanel() {
    // make panel fill vertical space.
    set_v_size_flags(SIZE_EXPAND_FILL);

    godot::ResourceLoader *res_loader = memnew( godot::ResourceLoader );

    {
        auto container = memnew( godot::HSplitContainer() );
        container->set_split_offset( 184 );
        container->set_anchors_preset( godot::Control::PRESET_FULL_RECT );

        {
            auto sidebar = memnew(godot::VBoxContainer);
            sidebar->set_v_size_flags(SIZE_EXPAND_FILL);

            {
                _start_button = memnew( godot::Button() );
                _start_button->set_text( "Start Server" );
                _start_button->connect("pressed", godot::Callable(this, "_on_start_button_pressed"));
                sidebar->add_child( _start_button );
            }

            {

            }

            container->add_child( sidebar );
        }

        {
            auto viewport_container = memnew( godot::SubViewportContainer );
            viewport_container->set_h_size_flags( SIZE_EXPAND_FILL );
            viewport_container->set_v_size_flags( SIZE_EXPAND_FILL );
            viewport_container->set_stretch(true); // expand viewport to fill

            {
                auto env = memnew( godot::Environment );
                env->set_background( godot::Environment::BG_COLOR );
                env->set_bg_color( godot::Color( 0, 0, 0, 1 ) );

                auto viewport = memnew( godot::SubViewport() );
                viewport->set_update_mode( godot::SubViewport::UpdateMode::UPDATE_ALWAYS );
                viewport->set_handle_input_locally( false );
                viewport->set_msaa_3d(godot::Viewport::MSAA_2X);
                viewport->set_screen_space_aa(godot::Viewport::SCREEN_SPACE_AA_FXAA);
                viewport->set_use_debanding(true);

                auto world = memnew(godot::World3D);
                world->set_environment(env);

                // Make the viewport use its own world, so
                // that it doesn't render the other contexts.
                viewport->set_world_3d(world);

                {
                    // Add an environment to draw a black background.
                    auto world_env = memnew( godot::WorldEnvironment );
                    world_env->set_environment( env );

                    // Add the camera.
                    auto camera = memnew( godot::Camera3D() );
                    camera->set_position(godot::Vector3(0, 0, 0.4)); // back the camera away from the model
                    world_env->add_child( camera );

                    viewport->add_child( world_env );

                    // Add a mesh instance to draw the face model.

                    _mesh_instance = memnew( godot::MeshInstance3D );

                    godot::Ref<godot::ArrayMesh> face =
                        res_loader->load( "res://addons/vdot/assets/tracking/live_link/face.res" );
                    if ( !face.is_valid() ) {
                        godot::UtilityFunctions::push_error(
                            "Failed to load face model for editor LiveLink preview." );
                    } else {
                        // NOTE: Due to how the files are copied over as part of the plugin,
                        //  setting the material and texture links via the editor results in them
                        //  not coming over correctly - hence loading and set them manually.
                        godot::Ref<godot::BaseMaterial3D> head_mat = res_loader->load(
                            "res://addons/vdot/assets/tracking/live_link/head_material.tres" );
                        if ( !head_mat.is_valid() ) {
                            godot::UtilityFunctions::push_error(
                                "Failed to load head material for editor LiveLink preview." );
                        }

                        godot::Ref<godot::Texture2D> head_tex = res_loader->load(
                            "res://addons/vdot/assets/tracking/live_link/face.png" );
                        if ( !head_tex.is_valid() ) {
                            godot::UtilityFunctions::push_error(
                                "Failed to load head texture for editor LiveLink preview." );
                        }

                        head_mat->set_texture( godot::BaseMaterial3D::TEXTURE_ALBEDO, head_tex );
                        face->surface_set_material( 0, head_mat );

                        _mesh_instance->set_mesh( face );
                    }
                    viewport->add_child( _mesh_instance );
                }
                viewport_container->add_child( viewport );
            }
            container->add_child( viewport_container );
        }
        add_child( container );
    }

    _server = memnew( LiveLinkServer );

    // we manually poll in relationship to if the panel is active or not.
    _server->_disable_polling = true;

    _server->connect( "client_connected", godot::Callable( this, "_on_server_client_connected" ) );
    _server->connect( "client_disconnected",
                      godot::Callable( this, "_on_server_client_disconnected" ) );
    _server->connect( "client_updated", godot::Callable( this, "_on_server_client_updated" ) );

    add_child(_server);
}

LiveLinkPanel::~LiveLinkPanel() {

}

void LiveLinkPanel::_process( double delta ) {
    if ( _server_active ) {
        _server->poll();
    }
}

godot::StringName LiveLinkPanel::blend_shape_name( int i ) {
    // TODO: optimize
    return godot::Array::make(
        "eyeBlinkLeft", "eyeLookDownLeft", "eyeLookInLeft",
        "eyeLookOutLeft", "eyeLookUpLeft", "eyeSquintLeft",
        "eyeWideLeft", "eyeBlinkRight", "eyeLookDownRight",
        "eyeLookInRight", "eyeLookOutRight",
        "eyeLookUpRight", "eyeSquintRight", "eyeWideRight",
        "jawForward", "jawRight", "jawLeft",
        "jawOpen", "mouthClose", "mouthFunnel",
        "mouthPucker", "mouthRight", "mouthLeft",
        "mouthSmileLeft", "mouthSmileRight",
        "mouthFrownLeft", "mouthFrownRight",
        "mouthDimpleLeft", "mouthDimpleRight",
        "mouthStretchLeft", "mouthStretchRight",
        "mouthRollLower", "mouthRollUpper",
        "mouthShrugLower", "mouthShrugUpper",
        "mouthPressLeft", "mouthPressRight",
        "mouthLowerDownLeft", "mouthLowerDownRight",
        "mouthUpperUpLeft", "mouthUpperUpRight",
        "browDownLeft", "browDownRight", "browInnerUp",
        "browOuterUpLeft", "browOuterUpRight", "cheekPuff",
        "cheekSquintLeft", "cheekSquintRight",
        "noseSneerLeft", "noseSneerRight", "tongueOut",
        "headYaw", "headPitch", "headRoll",
        "leftEyeYaw", "leftEyePitch", "leftEyeRoll",
        "rightEyeYaw", "rightEyePitch", "rightEyeRoll" )[i];
}

void LiveLinkPanel::start_server() {
    godot::UtilityFunctions::print("Starting LiveLinkFace server on: ", _server->get_port());

    _server->listen();
    _server_active = true;
    _start_button->set_text( "Stop Server" );
}

void LiveLinkPanel::stop_server() {
    godot::UtilityFunctions::print("Stopping LiveLinkFace server on: ", _server->get_port());

    _server_active = false;
    _server->stop();
    _start_button->set_text( "Start Server" );
}

void LiveLinkPanel::update_mesh( const LiveLinkClientData *data ) {
    //    auto rotation = godot::Vector3(
    //                        - data->_get_head_pitch(),
    //                        data->_get_head_yaw(),
    //                        data->_get_head_roll()) * 0.1;

    // 51 = limit of ARKit blendshapes in the data packet, rest are head position.
    for ( int i = 0; i < 51; ++i ) {
        auto value = data->_data[i];
        // tODO: cache blendshape indexes
        auto shape = _mesh_instance->find_blend_shape_by_name( blend_shape_name( i ) );
        if (shape > -1) {
            _mesh_instance->set_blend_shape_value( shape, value );
        } else {
            godot::UtilityFunctions::push_warning("Failed to find blendshape for index ", i, " looking for \"", blend_shape_name( i ), "\"");
        }
    }
}

void LiveLinkPanel::_on_start_button_pressed() {
    if (_server_active) {
        stop_server();
    } else {
        start_server();
    }
}

void LiveLinkPanel::_on_server_client_connected( LiveLinkClient *client ) {
}

void LiveLinkPanel::_on_server_client_disconnected( LiveLinkClient *client ) {
}

void LiveLinkPanel::_on_server_client_updated( LiveLinkClient *client ) {
    update_mesh( client->_values );
}

