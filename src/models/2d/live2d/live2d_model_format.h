

#ifndef VDOT_LIVE2D_MODEL_FORMAT_H
#define VDOT_LIVE2D_MODEL_FORMAT_H

#include "models/model_format.h"

class Live2DModelFormat : public ModelFormat {
    GDCLASS( Live2DModelFormat, ModelFormat )
  protected:
    static void _bind_methods();
  public:

    [[nodiscard]] godot::PackedStringArray get_supported_formats() const override;
    godot::String get_bundle_type() const override;
    Model* create_from_bundle(const godot::Ref<ModelBundle>& p_bundle, const godot::String& p_extract_path) override;
};

#endif // VDOT_LIVE2D_MODEL_FORMAT_H
