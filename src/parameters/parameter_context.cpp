
#include "parameter_context.h"
#include "parameter_input.h"

void ParameterContext::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "parameter_added", godot::PropertyInfo( godot::Variant::OBJECT, "parameter",
                                                godot::PROPERTY_HINT_TYPE_STRING, Parameter::get_class_static()) ) );

    ADD_SIGNAL( godot::MethodInfo(
        "parameters_updated", godot::PropertyInfo( godot::Variant::ARRAY, "parameters",
                                                godot::PROPERTY_HINT_ARRAY_TYPE, Parameter::get_class_static()) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_context_id" ),
                                 &ParameterContext::get_context_id );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "context_id" ),
                  godot::String(), "get_context_id" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_context_name" ),
                                 &ParameterContext::get_context_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "context_name" ),
                  godot::String(), "get_context_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_context_description" ),
                                 &ParameterContext::get_context_description );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "context_description" ),
                  godot::String(), "get_context_description" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_context_parameters", "context_parameters" ),
                                 &ParameterContext::set_context_parameters );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_context_parameters" ),
                                 &ParameterContext::get_context_parameters );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "context_parameters",
                                       godot::PROPERTY_HINT_ARRAY_TYPE, Parameter::get_class_static()),
                  "set_context_parameters", "get_context_parameters" );

    godot::ClassDB::bind_method( godot::D_METHOD( "add_input_parameter", "input_parameter" ),
                                 &ParameterContext::add_input_parameter );
}

godot::String ParameterContext::get_context_id() const {
    return context_id;
}

godot::String ParameterContext::get_context_name() const {
    return context_name;
}

godot::String ParameterContext::get_context_description() const {
    return context_description;
}

godot::TypedArray<Parameter> ParameterContext::get_context_parameters() const {
    return context_parameters;
}

void ParameterContext::set_context_parameters(const godot::TypedArray<Parameter>& p_parameters) {
    context_parameters = p_parameters;

    emit_signal("parameters_updated", context_parameters);
}

void ParameterContext::add_input_parameter(const godot::Ref<InputParameter>& p_parameter) {
    context_parameters.append(p_parameter);

    emit_signal("parameter_added", p_parameter);
}
