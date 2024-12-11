

#ifndef VDOT_MODEL_FORMAT_H
#define VDOT_MODEL_FORMAT_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "model_bundle.h"

/**
 * Provides methods for packaging and un-packaging models.
 */
class ModelFormat : public godot::Object {
    GDCLASS( ModelFormat, godot::Object )
  protected:
    // should be set in the constructor by implementations.
    // used to determine the model format to load with.
    godot::StringName format_type = "unknown";

    static void _bind_methods();

    static godot::String get_model_directory_path( const godot::String &p_name );

  public:
    [[nodiscard]] godot::StringName get_format_type() const;

    /**
     * Loads a model bundle from an existing location on the disk.
     *
     * Leaves the model in place at the provided location.
     *
     * @param p_path - path to the model.
     * @return the derived model bundle.
     */
    virtual godot::Ref<ModelBundle> load_model( const godot::String &p_path ) const {
        godot::UtilityFunctions::push_warning( "ModelFormat.import_model not implemented" );
        return nullptr;
    };

    virtual godot::Ref<ModelBundle> import_model( const godot::String &p_path ) const {
        godot::UtilityFunctions::push_warning( "ModelFormat.import_model not implemented" );
        return nullptr;
    };
};

#endif // VDOT_MODEL_FORMAT_H
