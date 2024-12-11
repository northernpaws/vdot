
#ifndef VDOT_MODEL_LOADER_H
#define VDOT_MODEL_LOADER_H

#include <godot_cpp/classes/object.hpp>

#include "model_format.h"

/**
 * Singleton for loading models.
 */
class ModelLoader : public godot::Object {
    GDCLASS( ModelLoader, godot::Object )
  protected:
    static constexpr const char* BUNDLE_EXTRACT_BASE_PATH = "user://temp/bundles/models";

    static ModelLoader* singleton;

    godot::TypedArray<ModelFormat> formats;

    static void _bind_methods();
  public:
    static ModelLoader* get_singleton() {
        return singleton;
    }

    ModelLoader();

    void add_model_format(const godot::Ref<ModelFormat>& p_format);

    [[nodiscard]] godot::Ref<ModelFormat> find_format(const godot::String& p_format) const;

    [[nodiscard]] godot::Ref<ModelBundle> load_bundle(const godot::String& p_path) const;
    [[nodiscard]] Model* create_from_bundle(const godot::Ref<ModelBundle>& p_bundle) const;
};

#endif // VDOT_MODEL_LOADER_H
