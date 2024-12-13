

#ifndef VDOT_PARAMETER_H
#define VDOT_PARAMETER_H

#include <godot_cpp/classes/resource.hpp>

class Parameter : public godot::Resource {
    GDCLASS( Parameter, godot::Resource )
  protected:
    static void _bind_methods();

  public:
    godot::StringName parameter_id; // unique for the parameter

    godot::String parameter_label;        // user-friendly name
    godot::String parameter_description; // user-friendly description

    godot::PackedStringArray parameter_tags; // contextual user-facing hints

    float parameter_minimum = 0.0f;
    float parameter_maximum = 1.0f;

    float parameter_default = 0.0f;

    [[nodiscard]] godot::StringName get_parameter_id() const;

    [[nodiscard]] godot::String get_parameter_label() const;
    [[nodiscard]] godot::String get_parameter_description() const;

    [[nodiscard]] godot::PackedStringArray get_parameter_tags() const;

    [[nodiscard]] float get_parameter_minimum_value() const;
    [[nodiscard]] float get_parameter_maximum_value() const;

    [[nodiscard]] float get_parameter_default_value() const;
};

#endif // VDOT_PARAMETER_H
