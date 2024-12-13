

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

    godot::HashMap<godot::StringName, godot::Ref<ParameterContext>> parameter_contexts;

    static void _bind_methods();

  public:
    static constexpr const char *SIGNAL_CONTEXT_ADDED = "context_added";
    static constexpr const char *SIGNAL_CONTEXT_REMOVED = "context_removed";

    static constexpr const char *SIGNAL_CONTEXT_PARAMETER_ADDED = "context_parameter_added";
    static constexpr const char *SIGNAL_CONTEXT_PARAMETER_REMOVED = "context_parameter_removed";

    static ParameterServer *get_singleton();

    ParameterServer();

    [[nodiscard]] godot::HashMap<godot::StringName, godot::Ref<ParameterContext>>
        get_parameter_contexts() const;
    void set_parameter_contexts(
        const godot::HashMap<godot::StringName, godot::Ref<ParameterContext>>
            &p_parameter_contexts );

    [[nodiscard]] godot::Ref<ParameterContext> get_parameter_context(
        const godot::StringName &p_context_id ) const;
    [[nodiscard]] godot::TypedArray<godot::StringName> list_context_ids() const;

    void add_parameter_context( const godot::Ref<ParameterContext> &p_parameter_context );
    void remove_parameter_context( const godot::Ref<ParameterContext> &p_parameter_context );

    [[nodiscard]] godot::Ref<InputParameter> get_input_parameter(
        const godot::StringName &p_id ) const;

    void _context_parameter_added( const godot::StringName &p_context_id,
                                   const godot::Ref<InputParameter> &p_parameter );
    void _context_parameter_removed( const godot::StringName &p_context_id,
                                     const godot::Ref<InputParameter> &p_parameter );
};

#endif // VDOT_PARAMETER_SERVER_H
