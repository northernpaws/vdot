

#include "avatar_parameter.h"

void AvatarParameter::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_id" ),
                                 &AvatarParameter::get_parameter_id );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_id", "id" ),
                                 &AvatarParameter::set_parameter_id );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING_NAME, "id" ), "set_parameter_id",
                  "get_parameter_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_name" ),
                                 &AvatarParameter::get_parameter_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_name", "name" ),
                                 &AvatarParameter::set_parameter_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "name" ), "set_parameter_name",
                  "get_parameter_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_description" ),
                                 &AvatarParameter::get_parameter_description );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_description", "description" ),
                                 &AvatarParameter::set_parameter_description );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "description" ),
                  "set_parameter_description", "get_parameter_description" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_input_range" ),
                                 &AvatarParameter::get_input_range );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_input_range", "range" ),
                                 &AvatarParameter::set_input_range );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2, "input_range" ), "set_input_range",
                  "get_input_range" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_output_range" ),
                                 &AvatarParameter::get_output_range );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_output_range", "range" ),
                                 &AvatarParameter::set_output_range );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2, "output_range" ),
                  "set_output_range", "get_output_range" );

    godot::ClassDB::bind_method( godot::D_METHOD( "calculate_value", "input", "delta" ),
                                 &AvatarParameter::calculate_value );
}

godot::StringName AvatarParameter::get_parameter_id() const {
    return parameter_id;
}

void AvatarParameter::set_parameter_id( const godot::StringName &p_id ) {
    parameter_id = p_id;
}

godot::String AvatarParameter::get_parameter_name() const {
    return parameter_name;
}

void AvatarParameter::set_parameter_name( const godot::String &p_name ) {
    parameter_name = p_name;
}

godot::String AvatarParameter::get_parameter_description() const {
    return parameter_description;
}

void AvatarParameter::set_parameter_description( const godot::String &p_description ) {
    parameter_description = p_description;
}

godot::Vector2 AvatarParameter::get_input_range() const {
    return input_range;
}

void AvatarParameter::set_input_range( const godot::Vector2 &p_range ) {
    input_range = p_range;
}

godot::Vector2 AvatarParameter::get_output_range() const {
    return output_range;
}

void AvatarParameter::set_output_range( const godot::Vector2 &p_range ) {
    output_range = p_range;
}

float AvatarParameter::calculate_value( float p_input, double delta ) const {
    // TODO: delta smoothing

    return ( ( ( p_input - input_range.x ) * ( output_range.y - output_range.x ) ) /
             ( input_range.y - input_range.x ) ) +
           output_range.x;
}
