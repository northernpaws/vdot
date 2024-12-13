

#ifndef VDOT_PARAMETER_CONTEXT_H
#define VDOT_PARAMETER_CONTEXT_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/hash_map.hpp>

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
    static constexpr const char *SIGNAL_PARAMETER_ADDED = "parameter_added";
    static constexpr const char *SIGNAL_PARAMETER_REMOVED = "parameter_removed";

    godot::String context_id;
    godot::String context_label;
    godot::String context_description;

    godot::HashMap<godot::StringName, godot::Ref<InputParameter>> context_parameters;

    [[nodiscard]] godot::String get_context_id() const;
    [[nodiscard]] godot::String get_context_label() const;
    [[nodiscard]] godot::String get_context_description() const;

    [[nodiscard]] godot::HashMap<godot::StringName, godot::Ref<InputParameter>>
        get_context_parameters() const;
    void set_context_parameters(
        const godot::HashMap<godot::StringName, godot::Ref<InputParameter>> &p_parameters );

    void add_input_parameter( const godot::Ref<InputParameter> &p_parameter );
    void remove_input_parameter( const godot::StringName &p_parameter_name );

    [[nodiscard]] bool has_input_parameter( const godot::StringName &p_name ) const;
    [[nodiscard]] godot::Ref<InputParameter> get_input_parameter(
        const godot::StringName &p_name ) const;

    [[nodiscard]] godot::TypedArray<godot::StringName> list_parameters() const;
};

#endif // VDOT_PARAMETER_CONTEXT_H
