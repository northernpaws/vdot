

#ifndef VDOT_MODEL_FORMAT_H
#define VDOT_MODEL_FORMAT_H

#include <godot_cpp/classes/object.hpp>

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

  public:
    [[nodiscard]] godot::StringName get_format_type() const;
};

#endif // VDOT_MODEL_FORMAT_H
