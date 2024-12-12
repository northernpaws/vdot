

#ifndef VDOT_PARAMETER_CONTEXT_H
#define VDOT_PARAMETER_CONTEXT_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "parameter.h"
#include "parameter_input.h"

/**
 * Groups a collection of related parameters, typically
 *  associated with something else that provides them.
 */
class ParameterContext : public godot::RefCounted {
    GDCLASS( ParameterContext, godot::RefCounted )
  protected:
    static void _bind_methods();
  public:
    godot::String context_id;
    godot::String context_name;
    godot::String context_description;

    godot::TypedArray<Parameter> context_parameters;

    [[nodiscard]] godot::String get_context_id() const;
    [[nodiscard]] godot::String get_context_name() const;
    [[nodiscard]] godot::String get_context_description() const;

    [[nodiscard]] godot::TypedArray<Parameter> get_context_parameters() const;
    void set_context_parameters(const godot::TypedArray<Parameter>& p_parameters);
    void add_input_parameter(const godot::Ref<InputParameter>& p_parameter);
};

#endif // VDOT_PARAMETER_CONTEXT_H
