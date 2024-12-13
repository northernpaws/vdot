

#include "parameter_server.h"

ParameterServer *ParameterServer::singleton = nullptr;

void ParameterServer::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo( SIGNAL_CONTEXT_ADDED,
                                   godot::PropertyInfo( godot::Variant::OBJECT, "context",
                                                        godot::PROPERTY_HINT_TYPE_STRING,
                                                        ParameterContext::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo( SIGNAL_CONTEXT_REMOVED,
                                   godot::PropertyInfo( godot::Variant::OBJECT, "context",
                                                        godot::PROPERTY_HINT_TYPE_STRING,
                                                        ParameterContext::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo(
        SIGNAL_CONTEXT_PARAMETER_ADDED,
        godot::PropertyInfo( godot::Variant::OBJECT, "context", godot::PROPERTY_HINT_TYPE_STRING,
                             ParameterContext::get_class_static() ),
        godot::PropertyInfo( godot::Variant::OBJECT, "parameter", godot::PROPERTY_HINT_TYPE_STRING,
                             InputParameter::get_class_static() ) ) );

    ADD_SIGNAL( godot::MethodInfo(
        SIGNAL_CONTEXT_PARAMETER_REMOVED,
        godot::PropertyInfo( godot::Variant::OBJECT, "context", godot::PROPERTY_HINT_TYPE_STRING,
                             ParameterContext::get_class_static() ),
        godot::PropertyInfo( godot::Variant::OBJECT, "parameter", godot::PROPERTY_HINT_TYPE_STRING,
                             InputParameter::get_class_static() ) ) );


    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_context", "context_id" ),
                                 &ParameterServer::get_parameter_context );

    godot::ClassDB::bind_method( godot::D_METHOD( "list_context_ids" ),
                                 &ParameterServer::list_context_ids );

    godot::ClassDB::bind_method( godot::D_METHOD( "add_parameter_context", "parameter_context" ),
                                 &ParameterServer::add_parameter_context );
    godot::ClassDB::bind_method( godot::D_METHOD( "remove_parameter_context", "context_id" ),
                                 &ParameterServer::remove_parameter_context );

    godot::ClassDB::bind_method( godot::D_METHOD( "_context_parameter_added" ),
                                 &ParameterServer::_context_parameter_added );
    godot::ClassDB::bind_method( godot::D_METHOD( "_context_parameter_removed" ),
                                 &ParameterServer::_context_parameter_removed );
}

ParameterServer *ParameterServer::get_singleton() {
    return singleton;
}

ParameterServer::ParameterServer() {
    singleton = this;
}

godot::HashMap<godot::StringName, godot::Ref<ParameterContext>> ParameterServer::
    get_parameter_contexts() const {
    return parameter_contexts;
}

void ParameterServer::set_parameter_contexts(
    const godot::HashMap<godot::StringName, godot::Ref<ParameterContext>> &p_parameter_contexts ) {
    parameter_contexts = p_parameter_contexts;
}

godot::Ref<ParameterContext> ParameterServer::get_parameter_context(
    const godot::StringName &p_context_id ) const {
    ERR_FAIL_COND_V_MSG(
        !parameter_contexts.has( p_context_id ), nullptr,
        godot::vformat( "Requested context '%s' does not exist.", p_context_id ) );

    return parameter_contexts[p_context_id];
}

godot::TypedArray<godot::StringName> ParameterServer::list_context_ids() const {
    godot::TypedArray<godot::StringName> context_ids;

    for ( const godot::KeyValue<godot::StringName, godot::Ref<ParameterContext>>
              &parameter_context : parameter_contexts ) {
        context_ids.append( parameter_context.key );
    }

    return context_ids;
}

void ParameterServer::add_parameter_context(
    const godot::Ref<ParameterContext> &p_parameter_context ) {
    parameter_contexts[p_parameter_context->context_id] = p_parameter_context;

    p_parameter_context->connect( ParameterContext::SIGNAL_PARAMETER_ADDED,
                                  godot::Callable( this, "_context_parameter_added" ) );

    emit_signal( SIGNAL_CONTEXT_ADDED, p_parameter_context );
}

void ParameterServer::remove_parameter_context(
    const godot::Ref<ParameterContext> &p_parameter_context ) {

    p_parameter_context->connect( ParameterContext::SIGNAL_PARAMETER_REMOVED,
                                  godot::Callable( this, "_context_parameter_removed" ) );

    emit_signal( SIGNAL_CONTEXT_REMOVED, p_parameter_context );

    parameter_contexts[p_parameter_context->context_id] = p_parameter_context;
}

godot::Ref<InputParameter> ParameterServer::get_input_parameter(
    const godot::StringName &p_name ) const {
    for ( const godot::KeyValue<godot::StringName, godot::Ref<ParameterContext>>
              &parameter_context : parameter_contexts ) {
        if ( parameter_context.value->has_input_parameter( p_name ) ) {
            return parameter_context.value->get_input_parameter( p_name );
        }
    }

    return nullptr;
}

void ParameterServer::_context_parameter_added( const godot::StringName &p_context_id,
                                                const godot::Ref<InputParameter> &p_parameter ) {
    ERR_FAIL_COND_MSG(
        !parameter_contexts.has( p_context_id ),
        godot::vformat( "Got signal for context '%s' which isn't registered.", p_context_id ) );

    emit_signal( SIGNAL_CONTEXT_PARAMETER_ADDED, parameter_contexts[p_context_id], p_parameter );
}

void ParameterServer::_context_parameter_removed( const godot::StringName &p_context_id,
                                                  const godot::Ref<InputParameter> &p_parameter ) {
    ERR_FAIL_COND_MSG(
        !parameter_contexts.has( p_context_id ),
        godot::vformat( "Got signal for context '%s' which isn't registered.", p_context_id ) );

    emit_signal( SIGNAL_CONTEXT_PARAMETER_REMOVED, parameter_contexts[p_context_id], p_parameter );
}