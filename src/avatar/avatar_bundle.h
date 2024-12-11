
#ifndef VDOT_AVATAR_BUNDLE_H
#define VDOT_AVATAR_BUNDLE_H

#include <godot_cpp/classes/resource.hpp>

#include "models/model_bundle.h"

/**
 * An avatar bundle encapsulates an avatar's config,
 *  model(s), etc. for storage or network transmission.
 */
class AvatarBundle : public godot::Resource {
    GDCLASS( AvatarBundle, godot::Resource )
  protected:
    godot::String name = "unnamed";

    godot::TypedArray<godot::Ref<ModelBundle>> models;

    static void _bind_methods();

  public:
    AvatarBundle();
    ~AvatarBundle() override;

    void set_avatar_name( const godot::String &p_name );
    [[nodiscard]] godot::String get_avatar_name() const;

    void set_models( const godot::TypedArray<ModelBundle> &p_models );
    [[nodiscard]] godot::TypedArray<ModelBundle> get_models() const;
    void add_model( const godot::Ref<ModelBundle> &p_model );
};

#endif // VDOT_AVATAR_BUNDLE_H
