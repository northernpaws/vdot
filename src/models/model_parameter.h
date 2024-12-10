

#ifndef VDOT_MODEL_PARAMETER_H
#define VDOT_MODEL_PARAMETER_H

#include <godot_cpp/classes/resource.hpp>

/**
 * Provides a handle to access a specific parameter for a model.
 *
 * This is a high-level method of allowing various model implementations to expose parameters,
 *  that can then be mapped as output parameters to various input parameters.
 */
// NOTE: implemented as a resource so that it supports saving/loading parameter values.
class ModelParameter : public godot::Resource {
    GDCLASS( ModelParameter, godot::Resource )
  protected:
    godot::StringName parameter_id; // unique for the model

    godot::String parameter_name; // user-friendly name
    godot::String parameter_description; // user-friendly description

    float parameter_minimum = 0.0f;
    float parameter_maximum = 1.0f;

    float parameter_value = 0.0f;

    static void _bind_methods();
  public:
    [[nodiscard]] godot::StringName get_parameter_id() const;

    [[nodiscard]] godot::String get_parameter_name() const;
    [[nodiscard]] godot::String get_parameter_description() const;

    [[nodiscard]] float get_parameter_minimum_value() const;
    [[nodiscard]] float get_parameter_maximum_value() const;

    [[nodiscard]] float get_parameter_value() const;
};

#endif // VDOT_MODEL_PARAMETER_H
