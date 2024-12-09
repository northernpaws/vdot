
#ifndef VDOT_AVATAR_H
#define VDOT_AVATAR_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/templates/hash_map.hpp>

#include "models/model.h"

#include "avatar_parameter.h"
#include "avatar_parameter_eval.h"

/**
 * The highest-level component for displaying a VTuber avatar.
 *
 * Encapsulates model rendering, motion tracking, parameters, etc.
 */
class Avatar : public godot::Sprite2D {
    GDCLASS( Avatar, godot::Sprite2D )
  protected:
    godot::TypedArray<godot::Ref<AvatarParameter>> parameters;
    godot::HashMap<godot::StringName, godot::Ref<AvatarParameterEval>> parameter_values;

    Model *model;

    static void _bind_methods();

  public:
    Avatar();
    ~Avatar() override;

    void _ready() override;
    void _process( double delta ) override;

    void _process_parameters( double delta );

    godot::PackedStringArray _get_configuration_warnings() const override;

    [[nodiscard]] godot::TypedArray<AvatarParameter> get_avatar_parameters() const;
    void set_avatar_parameters( const godot::TypedArray<AvatarParameter> &p_parameters );

    void _apply_parameter( const godot::StringName &p_id, float p_value );
};

#endif // VDOT_AVATAR_H
