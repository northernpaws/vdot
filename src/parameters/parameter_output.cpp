
#include "parameter_output.h"

void OutputParameter::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        SIGNAL_VALUE_CHANGED, godot::PropertyInfo( godot::Variant::FLOAT, "value",
                                                   godot::PROPERTY_HINT_TYPE_STRING, Parameter::get_class_static()) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_value" ),
                                 &OutputParameter::get_parameter_value );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_value", "value" ),
                                 &OutputParameter::set_parameter_value );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "parameter_value" ),
                  "set_parameter_value", "get_parameter_value" );
}
float OutputParameter::get_parameter_value() const {
    return parameter_value;
}

void OutputParameter::set_parameter_value( float value ) {
    parameter_value = value;

    emit_signal( SIGNAL_VALUE_CHANGED, parameter_value );
}
