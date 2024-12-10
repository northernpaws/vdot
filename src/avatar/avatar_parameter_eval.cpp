

#include "avatar_parameter_eval.h"

void AvatarParameterEval::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_id" ),
                                 &AvatarParameterEval::get_parameter_id );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING_NAME, "parameter_id" ),
                  godot::String(), "get_parameter_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_input" ),
                                 &AvatarParameterEval::get_parameter_input );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "parameter_input" ), godot::String(),
                  "get_parameter_input" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_value" ),
                                 &AvatarParameterEval::get_parameter_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "parameter_value" ), godot::String(),
                  "get_parameter_value" );
}

godot::StringName AvatarParameterEval::get_parameter_id() const {
    return parameter_id;
}

float AvatarParameterEval::get_parameter_input() const {
    return input;
}

float AvatarParameterEval::get_parameter_value() const {
    return value;
}