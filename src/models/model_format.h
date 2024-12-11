

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

    virtual godot::String get_format_loader_name() const { return godot::String(); }
    virtual godot::String get_format_loader_description() const { return godot::String(); }

    /**
     * Returns the list of file extensions that can be loaded by this format.
     * @return the recognized file extensions
     */
    [[nodiscard]] virtual godot::PackedStringArray get_recognized_extensions() const {
        return {};
    }

    /**
     * Alternative matches that's checked if get_recognized_extensions doesn't pass.
     * @return if the format can handle the specified path
     */
    [[nodiscard]] virtual bool can_handle_path(const godot::String& p_path) const {
        return false;
    }

    /**
     * Creates a model node from model sources at the provided filepath.
     * @param p_path the path to create the model from
     * @return the created model node
     */
    virtual Model* load_from_path(const godot::String& p_path) const {
        ERR_FAIL_V_MSG(nullptr, "create_from_path not implemented");
    }

    /**
     * Returns an array of format names to match against model bundle formats.
     */
    [[nodiscard]] virtual godot::PackedStringArray get_supported_formats() const {
        ERR_FAIL_V_MSG({}, "get_supported_formats not implemented");
    }

    /**
     * Returns the object class to use for loading models supported by this format.
     * @return the object class name
     */
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
