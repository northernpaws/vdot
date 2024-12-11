
#ifndef VDOT_AVATAR_H
#define VDOT_AVATAR_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/viewport_texture.hpp>
#include <godot_cpp/templates/hash_map.hpp>

#include "models/model.h"

#include "avatar_bundle.h"
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
    godot::TypedArray<AvatarParameter> parameters;
    godot::HashMap<godot::StringName, godot::Ref<AvatarParameterEval>> parameter_values;

    godot::Ref<godot::ViewportTexture> viewport_texture;

    Model *model;

    static void _bind_methods();

  public:
    Avatar();
    ~Avatar() override;

    void _validate_property(godot::PropertyInfo &p_property) const;

    void _notification(int p_what);

    void _ready() override;
    void _process( double delta ) override;

    void _process_parameters( double delta );

    [[nodiscard]] godot::PackedStringArray _get_configuration_warnings() const override;

    /**
     * Retrieve the list of avatar parameters.
     * @return list of avatar parameters
     */
    [[nodiscard]] godot::TypedArray<AvatarParameter> get_avatar_parameters() const;

    /**
     * Set the list of parameters for the avatar.
     * @param p_parameters new avatar parameters
     */
    void set_avatar_parameters( const godot::TypedArray<AvatarParameter> &p_parameters );

    /**
     * Applies the parameter with the specified pre-calculated "output" value.
     * @param p_id id of the parameter to apply
     * @param p_value value to apply to the parameter
     */
    void _apply_parameter( const godot::StringName &p_id, float p_value );

    /**
     * Pack the avatar and it's resources into a bundle for transmission.
     *
     * Primarily intended for use with networked collaboration sessions.
     *
     * @return the avatar bundle
     */
    godot::Ref<AvatarBundle> pack_bundle() const;

    void _child_entered_tree(godot::Node* p_node);
    void _child_exiting_tree(godot::Node* p_node);
};

#endif // VDOT_AVATAR_H
