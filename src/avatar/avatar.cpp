
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/multiplayer_peer.hpp>

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::NODE_PATH, "model", godot::PROPERTY_HINT_TYPE_STRING,
                             Model::get_class_static() ),
        godot::String(), "get_model" );

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
//    if (p_property.name == godot::StringName("centered") ||
//         p_property.name == godot::StringName("flip_h") ||
//         p_property.name == godot::StringName("flip_v") ||
//         p_property.name == godot::StringName("frame") ||
//         p_property.name == godot::StringName("frame_coords") ||
//         p_property.name == godot::StringName("hframes") ||
//         p_property.name == godot::StringName("offset") ||
//         p_property.name == godot::StringName("region_enabled") ||
//         p_property.name == godot::StringName("region_filter_clip_enabled") ||
//         p_property.name == godot::StringName("region_rect") ||
//         p_property.name == godot::StringName("texture") ||
//         p_property.name == godot::StringName("vframes")) {
//        p_property.usage &= ~godot::PROPERTY_USAGE_EDITOR;
//    }
}

void Avatar::_notification(int p_what) {
    // Ensure we update the model texture references
    //  if the node path or parented status changes.
    if (p_what == godot::Node::NOTIFICATION_PATH_RENAMED ||
         p_what == godot::Node::NOTIFICATION_POST_ENTER_TREE ||
         p_what == godot::Node::NOTIFICATION_PARENTED ||
         p_what == godot::Node::NOTIFICATION_UNPARENTED) {
        // Ensure we update the texture to reference the new path.
        _update_model_references();
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

    _update_model_references();
}

void Avatar::_enter_tree() {
    _update_model_references();
}

void Avatar::_exit_tree() {
    _update_model_references();
}

void Avatar::_input(const godot::Ref<godot::InputEvent> &p_event) {
    godot::Ref<godot::InputEventMouseButton> mouse_button = p_event;
    if (mouse_button.is_valid()) {
        if (mouse_button->get_button_index() == godot::MOUSE_BUTTON_LEFT) {
            if (mouse_button->is_pressed()) {
                mouse_dragging = true;

                // Offset so that the sprite doesn't "snap" to the mouse center.
                drag_offset = get_global_position() - mouse_button->get_global_position();
            } else {
                mouse_dragging = false;
            }
        } else if (mouse_button->get_button_index() == godot::MOUSE_BUTTON_WHEEL_UP) {
            set_scale(godot::Vector2(get_scale().x + 0.02f, get_scale().y + 0.02f));
        } else if (mouse_button->get_button_index() == godot::MOUSE_BUTTON_WHEEL_DOWN) {
            set_scale(godot::Vector2(get_scale().x - 0.02f, get_scale().y - 0.02f));
        }
    }

    godot::Ref<godot::InputEventMouseMotion> mouse_motion = p_event;
    if (mouse_motion.is_valid() && mouse_dragging) {
        set_global_position(mouse_motion->get_global_position() + drag_offset);
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
    if (model == nullptr ) {// children.size() == 0 ||
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
    _update_model_references();
}

void Avatar::_child_exiting_tree(godot::Node* p_node) {
    _update_model_references();
}

void Avatar::_update_model_references() {
    if (!is_inside_tree()) {
        model = nullptr;
        set_texture( nullptr );
        godot::UtilityFunctions::print("outside tree, cleared model and texture reference");
        return;
    }

    if (model == nullptr) {
        // TODO: ideally should be using auto children = find_children("*", Model::get_class_static(), true, true);
        //  but for some reason it wasn't working reliably here.
        auto children = get_children();
        for (int i = 0; i < children.size(); i++) {
            auto* child = godot::Object::cast_to<godot::Node>(children[i]);

            if (godot::ClassDB::is_parent_class(Model::get_class_static(), child->get_class_static())) {
                model = godot::Object::cast_to<Model>(child);
                godot::UtilityFunctions::print("found model in children");
                break;
            }
        }

        if (model == nullptr) {
            godot::UtilityFunctions::print("no model found in children");
        }
    }

    if (model == nullptr) {
        set_texture(nullptr);
        godot::UtilityFunctions::print("model null, cleared texture");
    } else {
        if (is_inside_tree()) {
            godot::UtilityFunctions::print("inside tree, set texture");
            set_texture( model->get_texture() );
        } else {
            godot::UtilityFunctions::print("outside tree, didn't set texture");
        }
    }

    update_configuration_warnings();
}