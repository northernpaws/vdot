
#ifndef VDOT_MODEL_H
#define VDOT_MODEL_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>

/**
 * Model provides the base class for VTuber avatar/model.
 *
 * Models are rendered in viewports to make various means of projecting
 *  and rendering them in different contexts them easier.
 */
class Model : public godot::SubViewport {
    GDCLASS( Model, godot::SubViewport )
  protected:
    godot::Array parameters;
  public:
    static void _bind_methods();

    [[nodiscard]] godot::Array get_model_parameters() const;
};

#endif // VDOT_MODEL_H
