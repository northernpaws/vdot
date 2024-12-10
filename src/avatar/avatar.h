
#ifndef VDOT_AVATAR_H
#define VDOT_AVATAR_H

#include <godot_cpp/classes/sprite2d.hpp>

#include "avatar_parameter.h"

/**
 * The highest-level component for displaying a VTuber avatar.
 *
 * Encapsulates model rendering, motion tracking, parameters, etc.
 */
class Avatar : public godot::Sprite2D {
    GDCLASS( Avatar, godot::Sprite2D )
  protected:
    godot::TypedArray<AvatarParameter> parameters;

    static void _bind_methods();
  public:
    Avatar();
    ~Avatar() override;

    void _process(double delta) override;

    [[nodiscard]] godot::TypedArray<AvatarParameter> get_avatar_parameters() const;
    void set_avatar_parameters(const godot::TypedArray<AvatarParameter>& p_parameters);
};

#endif // VDOT_AVATAR_H
