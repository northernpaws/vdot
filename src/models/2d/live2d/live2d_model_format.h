
#ifndef VDOT_LIVE2D_MODEL_FORMAT_H
#define VDOT_LIVE2D_MODEL_FORMAT_H

#include "models/model_format.h"

/**
 * A model format implementation for Live2D models.
 */
class Live2DModelFormat : public ModelFormat {
    GDCLASS( Live2DModelFormat, ModelFormat )
  protected:
    static void _bind_methods();

  public:
    Live2DModelFormat();

    godot::Ref<ModelBundle> load_model( const godot::String &p_path ) const override;
    [[nodiscard]] godot::Ref<ModelBundle> import_model(
        const godot::String &p_path ) const override;
};

#endif // VDOT_LIVE2D_MODEL_FORMAT_H
