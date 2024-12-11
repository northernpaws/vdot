
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/multiplayer_peer.hpp>
#include <godot_cpp/templates/hash_map.hpp>

#include "avatar.h"

void Avatar::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "parameter_evaluated", godot::PropertyInfo( godot::Variant::OBJECT, "parameter",
                                                    godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                    AvatarParameterEval::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo(
        "parameters_evaluated", godot::PropertyInfo( godot::Variant::DICTIONARY, "parameters" ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_parameters" ),
                                 &Avatar::get_avatar_parameters );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_parameters", "parameters" ),
                                 &Avatar::set_avatar_parameters );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::ARRAY, "parameters", godot::PROPERTY_HINT_TYPE_STRING,
                             godot::String::num( godot::Variant::OBJECT ) + "/" +
                                 godot::String::num( godot::PROPERTY_HINT_RESOURCE_TYPE ) + ":" +
                                 AvatarParameter::get_class_static() ),
        "set_avatar_parameters", "get_avatar_parameters" );

    godot::ClassDB::bind_method( godot::D_METHOD( "_apply_parameter", "id", "value" ),
                                 &Avatar::_apply_parameter );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_model" ),
                                 &Avatar::get_model );

    godot::ClassDB::bind_method( godot::D_METHOD( "_child_entered_tree", "node" ),
                                 &Avatar::_child_entered_tree );
    godot::ClassDB::bind_method( godot::D_METHOD( "_child_exiting_tree", "node" ),
                                 &Avatar::_child_exiting_tree );
}

Avatar::Avatar() {
    connect("child_entered_tree", godot::Callable(this, "_child_entered_tree"));
    connect("child_exiting_tree", godot::Callable(this, "_child_exiting_tree"));
}

Avatar::~Avatar() {
}

void Avatar::_validate_property(godot::PropertyInfo &p_property) const {
    // Hide the base Sprite2D properties.
    if (p_property.name == godot::StringName("centered") ||
         p_property.name == godot::StringName("flip_h") ||
         p_property.name == godot::StringName("flip_v") ||
         p_property.name == godot::StringName("frame") ||
         p_property.name == godot::StringName("frame_coords") ||
         p_property.name == godot::StringName("hframes") ||
         p_property.name == godot::StringName("offset") ||
         p_property.name == godot::StringName("region_enabled") ||
         p_property.name == godot::StringName("region_filter_clip_enabled") ||
         p_property.name == godot::StringName("region_rect") ||
         p_property.name == godot::StringName("texture") ||
         p_property.name == godot::StringName("vframes")) {
        p_property.usage &= ~godot::PROPERTY_USAGE_EDITOR;
    }
}

void Avatar::_notification(int p_what) {
    if (p_what == godot::Node::NOTIFICATION_PATH_RENAMED && model) {
        if (viewport_texture.is_valid()) {
            viewport_texture->set_viewport_path_in_scene( model->get_path() );
        }
    }
}

void Avatar::_ready() {
    {
        godot::Dictionary opts;
        // the RPC will be called by the peer "owning" the avatar.
        opts["rpc_mode"] = godot::MultiplayerAPI::RPC_MODE_ANY_PEER;
        // Parameter updates will be called often, and we don't need all of them to sync.
        opts["transfer_mode"] = godot::MultiplayerPeer::TRANSFER_MODE_UNRELIABLE_ORDERED;
        // Shortcut to prevent calling apply twice, have it call the local peer too.
        opts["call_local"] = true;
        opts["channel"] = 0; // TODO: allocate a channel specifically for avatar parameter updates
        rpc_config( "_apply_parameter", opts );
    }
}

void Avatar::_process( double delta ) {
    _process_parameters( delta );
}

void Avatar::_process_parameters( double delta ) {
    godot::Dictionary updated_parameter_values;

    // Loop over the parameters and
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<AvatarParameter> parameter = parameters[i];
        if ( !parameter.is_valid() ) {
            continue;
        }

        godot::Ref<AvatarParameterEval> eval = parameter_values[parameter->get_parameter_id()];

        // Retrieve the input value from the designated input parameter.
        auto input = 0.0f; // TODO: retrieve input value

        // Skip evaluating parameters without a changed input value.
        // TODO: don't skip is an avatar parameter setting changed
        if ( input == eval->input ) {
            continue;
        }

        eval->input = input;

        // Calculate the parameter value to feed into the model.
        //
        // This takes into account input and output range conversion, value
        // smoothing, and other possible transformations on the input value.
        eval->value = parameter->calculate_value( input, delta );

        // TODO: apply smoothing (use smoothstep?), use eval to store smoothing data.

        // Used in bulk-updated of parameter values.
        updated_parameter_values[parameter->get_parameter_id()] = eval;

        // NOTE: We emit before applying the value to give a chance
        //  for external systems to process it in parallel, as
        //  applying the value might take a moment.
        emit_signal( "parameter_evaluated", eval );

        // Apply the calculated parameter values to the target parameters.
        //
        // Use an RPC call to sync it over the network.
        _apply_parameter( parameter->get_parameter_id(), eval->value );
    }

    emit_signal( "parameters_evaluated", parameters );
}

Model * Avatar::get_model() const {
    return model;
}

godot::PackedStringArray Avatar::_get_configuration_warnings() const {
    godot::PackedStringArray warnings;

    auto children = find_children("*", Model::get_class_static(), true, true);
    if (children.size() == 0 || model == nullptr ) {
        warnings.push_back( "Avatar is missing a model. Add a node descended from Model to this node's children." );
    } else if (children.size() > 1) {
        warnings.push_back( "Avatar should only have one model child." );
    }

    return warnings;
}

godot::TypedArray<AvatarParameter> Avatar::get_avatar_parameters() const {
    return parameters;
}

void Avatar::set_avatar_parameters( const godot::TypedArray<AvatarParameter> &p_parameters ) {
    parameters = p_parameters;

    parameter_values.clear();
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<AvatarParameter> param = parameters[i];
        if ( !param.is_valid() ) {
            continue;
        }

        godot::Ref<AvatarParameterEval> eval;
        eval.instantiate();
        eval->parameter_id = param->get_parameter_id();

        parameter_values[param->get_parameter_id()] = eval;
    }
}

void Avatar::_apply_parameter( const godot::StringName &p_id, float p_value ) {
    //    rpc( "_apply_parameter", parameter->get_parameter_id(), eval->value );
}

godot::Ref<AvatarBundle> Avatar::pack_bundle() const {
    godot::Ref<AvatarBundle> bundle;
    bundle.instantiate();

    bundle->set_avatar_name( "Unnamed" );

    // TODO: pack avatar parameters

    if (model != nullptr) {
        auto model_bundle = model->pack_bundle();
        ERR_FAIL_COND_V_MSG(model_bundle.is_null(), {}, "Failed to pack model for avatar bundle.");

        bundle->add_model(model_bundle);
    } else {
        WARN_PRINT("No model is loaded for the Avatar. Packing the avatar to a bundle will effectively be blank.");
    }

    return bundle;
}

void Avatar::_child_entered_tree(godot::Node* p_node) {
    if (model == nullptr) {
        auto child = Object::cast_to<Model>(p_node);
        if (child != nullptr) {
            model = child;

            auto node_path = model->get_path();

            // Attach the viewport as the avatar sprite texture.
            viewport_texture.instantiate();
            viewport_texture->set_viewport_path_in_scene( model->get_path() );
            set_texture( viewport_texture );

            update_configuration_warnings();
        }
    }
}

void Avatar::_child_exiting_tree(godot::Node* p_node) {
    if (p_node == model) {
        model = nullptr;
        update_configuration_warnings();
    }
}