

#ifndef VDOT_AVATAR_PARAMETER_H
#define VDOT_AVATAR_PARAMETER_H

#include <godot_cpp/classes/resource.hpp>

/**
 * Defines a n input->output parameter mapping associated with the avatar.
 */
class AvatarParameter : public godot::Resource {
    GDCLASS( AvatarParameter, godot::Resource )
  protected:
    godot::StringName parameter_id; // unique for the model

    godot::String parameter_name;        // user-friendly name
    godot::String parameter_description; // user-friendly description

    godot::Vector2 input_range;
    godot::Vector2 output_range;

    static void _bind_methods();
  public:
    [[nodiscard]] godot::StringName get_parameter_id() const;
    void set_parameter_id(const godot::StringName& p_id);

    [[nodiscard]] godot::String get_parameter_name() const;
    void set_parameter_name(const godot::String& p_name);

    [[nodiscard]] godot::String get_parameter_description() const;
    void set_parameter_description(const godot::String& p_description);

    godot::Vector2 get_input_range() const;
    void set_input_range(const godot::Vector2& p_range);

    godot::Vector2 get_output_range() const;
    void set_output_range(const godot::Vector2& p_range);
};

#endif // VDOT_AVATAR_PARAMETER_H
