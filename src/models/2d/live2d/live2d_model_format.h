

#ifndef VDOT_LIVE2D_MODEL_FORMAT_H
#define VDOT_LIVE2D_MODEL_FORMAT_H

#include "models/model_format.h"

class Live2DModelFormat : public ModelFormat {
    GDCLASS( Live2DModelFormat, ModelFormat )
  protected:
    static void _bind_methods();

  public:
    [[nodiscard]] godot::String get_format_loader_name() const override {
        return "Live2D";
    }

    [[nodiscard]] godot::String get_format_loader_description() const override {
        return "Supports loading of Live2D .model3.json models.";
    }

    [[nodiscard]] godot::PackedStringArray get_recognized_extensions() const override;
    [[nodiscard]] bool can_handle_path( const godot::String &p_path ) const override;

    [[nodiscard]] Model *load_from_path( const godot::String &p_path ) const override;

    [[nodiscard]] godot::PackedStringArray get_supported_formats() const override;
    [[nodiscard]] godot::String get_bundle_type() const override;
    [[nodiscard]] Model *create_from_bundle( const godot::Ref<ModelBundle> &p_bundle,
                                             const godot::String &p_extract_path ) override;
};

#endif // VDOT_LIVE2D_MODEL_FORMAT_H
