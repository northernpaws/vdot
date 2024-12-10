
#include "model_parameter.h"

void ModelParameter::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "value_updated", godot::PropertyInfo( godot::Variant::STRING_NAME, "parameter_id" ),
        godot::PropertyInfo( godot::Variant::FLOAT, "parameter_value" ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_id" ),
                                 &ModelParameter::get_parameter_id );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING_NAME, "id" ), godot::String(),
                  "get_parameter_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_name" ),
                                 &ModelParameter::get_parameter_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "name" ), godot::String(),
                  "get_parameter_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_description" ),
                                 &ModelParameter::get_parameter_description );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "description" ), godot::String(),
                  "get_parameter_description" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_minimum_value" ),
                                 &ModelParameter::get_parameter_minimum_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "minimum_value" ), godot::String(),
                  "get_parameter_minimum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_maximum_value" ),
                                 &ModelParameter::get_parameter_maximum_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "maximum_value" ), godot::String(),
                  "get_parameter_maximum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_default_value" ),
                                 &ModelParameter::get_parameter_default_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "parameter_default_value" ),
                  godot::String(), "get_parameter_default_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_value" ),
                                 &ModelParameter::get_parameter_value );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_value" ),
                                 &ModelParameter::set_parameter_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "parameter_value" ),
                  "set_parameter_value", "get_parameter_value" );
}

godot::StringName ModelParameter::get_parameter_id() const {
    return parameter_id;
}

godot::String ModelParameter::get_parameter_name() const {
    return parameter_name;
}

godot::String ModelParameter::get_parameter_description() const {
    return parameter_description;
}

float ModelParameter::get_parameter_minimum_value() const {
    return parameter_minimum;
}

float ModelParameter::get_parameter_maximum_value() const {
    return parameter_maximum;
}

float ModelParameter::get_parameter_default_value() const {
    return parameter_default;
}

float ModelParameter::get_parameter_value() const {
    return parameter_value;
}

void ModelParameter::set_parameter_value( float value ) {
    parameter_value = value;

    emit_signal( "value_updated", parameter_id, parameter_value );
}