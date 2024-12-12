

#include "parameter_server.h"

ParameterServer *ParameterServer::singleton = nullptr;

void ParameterServer::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo( "parameter_registered",
                                   godot::PropertyInfo( godot::Variant::OBJECT, "input_parameter",
                                                        godot::PROPERTY_HINT_TYPE_STRING,
                                                        InputParameter::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo( "parameter_removed",
                                   godot::PropertyInfo( godot::Variant::OBJECT, "input_parameter",
                                                        godot::PROPERTY_HINT_TYPE_STRING,
                                                        InputParameter::get_class_static() ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "register_input_parameter", "input_parameter" ),
                                 &ParameterServer::register_input_parameter );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_input_parameters" ),
                                 &ParameterServer::get_input_parameters );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_input_parameters", "input_parameters" ),
                                 &ParameterServer::set_input_parameters );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "input_parameters",
                                       godot::PROPERTY_HINT_ARRAY_TYPE, InputParameter::get_class_static() ),
                  "set_input_parameters", "get_input_parameters" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_contexts" ),
                                 &ParameterServer::get_parameter_contexts );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_contexts", "parameter_contexts" ),
                                 &ParameterServer::set_parameter_contexts );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "parameter_contexts",
                                       godot::PROPERTY_HINT_ARRAY_TYPE, ParameterContext::get_class_static() ),
                  "set_parameter_contexts", "get_parameter_contexts" );
}

ParameterServer *ParameterServer::get_singleton() {
    return singleton;
}

ParameterServer::ParameterServer() {
    singleton = this;
}

void ParameterServer::register_input_parameter( const godot::Ref<InputParameter> &p_parameter ) {
    input_parameters.push_back( p_parameter );

    emit_signal( "parameter_registered", p_parameter );
}

void ParameterServer::remove_input_parameter( const godot::Ref<InputParameter> &p_parameter ) {
    emit_signal( "parameter_removed", p_parameter );
    input_parameters.erase( p_parameter );
}

godot::TypedArray<InputParameter> ParameterServer::get_input_parameters() const {
    return input_parameters;
}

void ParameterServer::set_input_parameters(
    const godot::TypedArray<InputParameter> &p_parameters ) {
    input_parameters = p_parameters;
}

godot::TypedArray<ParameterContext> ParameterServer::get_parameter_contexts() const {
    return parameter_contexts;
}

void ParameterServer::set_parameter_contexts( const godot::TypedArray<ParameterContext> &p_parameter_contexts ) {
    parameter_contexts = p_parameter_contexts;
}

void ParameterServer::add_parameter_context(const godot::Ref<ParameterContext> &p_parameter_context) {
    parameter_contexts.append(p_parameter_context);
}
