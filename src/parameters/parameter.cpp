
#include "parameter.h"

void Parameter::_bind_methods() {
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::STRING_NAME, "id", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_name" ),
                                 &Parameter::get_parameter_name );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::STRING, "name", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_description" ),
                                 &Parameter::get_parameter_description );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::STRING, "description", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_description" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_labels" ),
                                 &Parameter::get_parameter_labels );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::STRING, "labels", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_labels" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_minimum_value" ),
                                 &Parameter::get_parameter_minimum_value );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::FLOAT, "minimum_value", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_minimum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_maximum_value" ),
                                 &Parameter::get_parameter_maximum_value );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::FLOAT, "maximum_value", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_maximum_value" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_default_value" ),
                                 &Parameter::get_parameter_default_value );
    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::FLOAT, "default_value", godot::PROPERTY_HINT_NONE, "",
                             godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
        godot::String(), "get_parameter_default_value" );
}

godot::StringName Parameter::get_parameter_id() const {
    return parameter_id;
}

godot::String Parameter::get_parameter_name() const {
    return parameter_name;
}

godot::String Parameter::get_parameter_description() const {
    return parameter_description;
}

godot::PackedStringArray Parameter::get_parameter_labels() const {
    return parameter_labels;
}

float Parameter::get_parameter_minimum_value() const {
    return parameter_minimum;
}

float Parameter::get_parameter_maximum_value() const {
    return parameter_maximum;
}

float Parameter::get_parameter_default_value() const {
    return parameter_default;
}

