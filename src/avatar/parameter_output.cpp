
#include "parameter_output.h"


void OutputParameter::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "value_changed", godot::PropertyInfo( godot::Variant::STRING_NAME, "parameter_id" ),
        godot::PropertyInfo( godot::Variant::FLOAT, "parameter_value" ) ) );
    
    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_id" ),
                                 &OutputParameter::get_parameter_id );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING_NAME, "id", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_name" ),
                                 &OutputParameter::get_parameter_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "name", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_description" ),
                                 &OutputParameter::get_parameter_description );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "description", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_description" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_labels" ),
                                 &OutputParameter::get_parameter_labels );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "labels", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_labels" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_minimum_value" ),
                                 &OutputParameter::get_parameter_minimum_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "minimum_value", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_minimum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_maximum_value" ),
                                 &OutputParameter::get_parameter_maximum_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "maximum_value", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ), godot::String(),
                  "get_parameter_maximum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_default_value" ),
                                 &OutputParameter::get_parameter_default_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "default_value", godot::PROPERTY_HINT_NONE, "", godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
                  godot::String(), "get_parameter_default_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_value" ),
                                 &OutputParameter::get_parameter_value );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_value" ),
                                 &OutputParameter::set_parameter_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "value" ),
                  "set_parameter_value", "get_parameter_value" );
}

godot::StringName OutputParameter::get_parameter_id() const {
    return parameter_id;
}

godot::String OutputParameter::get_parameter_name() const {
    return parameter_name;
}

godot::String OutputParameter::get_parameter_description() const {
    return parameter_description;
}

godot::PackedStringArray OutputParameter::get_parameter_labels() const {
    return parameter_labels;
}

float OutputParameter::get_parameter_minimum_value() const {
    return parameter_minimum;
}

float OutputParameter::get_parameter_maximum_value() const {
    return parameter_maximum;
}

float OutputParameter::get_parameter_default_value() const {
    return parameter_default;
}

float OutputParameter::get_parameter_value() const {
    return parameter_value;
}

void OutputParameter::set_parameter_value( float value ) {
    parameter_value = value;

    emit_signal( "value_changed", parameter_id, parameter_value );
}
