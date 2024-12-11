

#ifndef VDOT_MODEL_FORMAT_H
#define VDOT_MODEL_FORMAT_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "model_bundle.h"
#include "model.h"

/**
 * Base class for implementing loaders for model formats.
 */
class ModelFormat : public godot::RefCounted {
    GDCLASS( ModelFormat, godot::RefCounted )
  protected:
    static void _bind_methods();
  public:

    [[nodiscard]] virtual godot::PackedStringArray get_supported_formats() const {
        ERR_FAIL_V_MSG({}, "get_supported_formats not implemented");
    }

    [[nodiscard]] virtual godot::String get_bundle_type() const {
        return ModelBundle::get_class_static();
    }

    /**
     * Create a model node from the provided model bundle.
     *
     * @param p_bundle - model bundle to create a model from.
     * @return the model node
     */
    virtual Model* create_from_bundle(const godot::Ref<ModelBundle>& p_bundle, const godot::String& p_extract_path) {
        ERR_FAIL_V_MSG(nullptr, "create_from_bundle not implemented");
    }
};

#endif // VDOT_MODEL_FORMAT_H
