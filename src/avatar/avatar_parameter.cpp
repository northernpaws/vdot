

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

    godot::ClassDB::bind_method( godot::D_METHOD( "get_input_parameter" ),
                                 &AvatarParameter::get_input_parameter );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_input_parameter", "input_parameter" ),
                                 &AvatarParameter::set_input_parameter );
    ADD_PROPERTY( godot::PropertyInfo(
                      godot::Variant::OBJECT, "input_parameter", godot::PROPERTY_HINT_TYPE_STRING,
                      InputParameter::get_class_static(),
                      godot::PROPERTY_USAGE_DEFAULT | godot::PROPERTY_USAGE_NEVER_DUPLICATE ),
                  "set_input_parameter", "get_input_parameter" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_output_parameter" ),
                                 &AvatarParameter::get_output_parameter );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_output_parameter", "output_parameter" ),
                                 &AvatarParameter::set_output_parameter );
    ADD_PROPERTY( godot::PropertyInfo(
                      godot::Variant::OBJECT, "output_parameter", godot::PROPERTY_HINT_TYPE_STRING,
                      OutputParameter::get_class_static(),
                      godot::PROPERTY_USAGE_DEFAULT | godot::PROPERTY_USAGE_NEVER_DUPLICATE ),
                  "set_output_parameter", "get_output_parameter" );

    godot::ClassDB::bind_method( godot::D_METHOD( "calculate_value", "input", "delta" ),
                                 &AvatarParameter::calculate_value );

    godot::ClassDB::bind_method( godot::D_METHOD( "_on_input_changed", "value" ),
                                 &AvatarParameter::_on_input_changed );
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

godot::Ref<InputParameter> AvatarParameter::get_input_parameter() const {
    return input_parameter;
}

void AvatarParameter::set_input_parameter( const godot::Ref<InputParameter> &p_input_parameter ) {
    if (input_parameter.is_valid()) {
        input_parameter->disconnect(InputParameter::SIGNAL_VALUE_CHANGED, godot::Callable(this, "_on_input_changed"));
    }

    input_parameter = p_input_parameter;

    input_range = godot::Vector2(input_parameter->parameter_minimum,
                                  input_parameter->parameter_maximum);

    input_parameter->connect(InputParameter::SIGNAL_VALUE_CHANGED, godot::Callable(this, "_on_input_changed"));
}

godot::Ref<OutputParameter> AvatarParameter::get_output_parameter() const {
    return output_parameter;
}

void AvatarParameter::set_output_parameter(
    const godot::Ref<OutputParameter> &p_output_parameter ) {
    output_parameter = p_output_parameter;

    output_range =
        godot::Vector2( output_parameter->parameter_minimum, output_parameter->parameter_maximum );
}

float AvatarParameter::calculate_value( float p_input, double delta ) const {
    // TODO: delta smoothing?

    return ( ( ( p_input - input_range.x ) * ( output_range.y - output_range.x ) ) /
             ( input_range.y - input_range.x ) ) +
           output_range.x;
}

void AvatarParameter::_on_input_changed(float p_input_value) {
    // TODO: signal for new value
}
