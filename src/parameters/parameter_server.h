

#ifndef VDOT_PARAMETER_SERVER_H
#define VDOT_PARAMETER_SERVER_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "parameter_context.h"
#include "parameter_input.h"

/**
 * Provides the server singleton used to access and bind to input parameters,
 *  and to register new input parameters created by other servers or nodes.
 */
class ParameterServer : public godot::RefCounted {
    GDCLASS( ParameterServer, godot::RefCounted )
  protected:
    static ParameterServer *singleton;

    godot::TypedArray<InputParameter> input_parameters;
    godot::TypedArray<ParameterContext> parameter_contexts;

    static void _bind_methods();

  public:
    static ParameterServer *get_singleton();

    ParameterServer();

    void register_input_parameter( const godot::Ref<InputParameter> &p_parameter );
    void remove_input_parameter( const godot::Ref<InputParameter> &p_parameter );

    [[nodiscard]] godot::TypedArray<InputParameter> get_input_parameters() const;
    void set_input_parameters( const godot::TypedArray<InputParameter> &p_parameters );

    [[nodiscard]] godot::TypedArray<ParameterContext> get_parameter_contexts() const;
    void set_parameter_contexts( const godot::TypedArray<ParameterContext> &p_parameter_contexts );
    void add_parameter_context(const godot::Ref<ParameterContext> &p_parameter_context);
    void remove_parameter_context(const godot::Ref<ParameterContext> &p_parameter_context);
};

#endif // VDOT_PARAMETER_SERVER_H
