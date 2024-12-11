
#ifndef VDOT_MODEL_H
#define VDOT_MODEL_H

#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>

#include "model_bundle.h"
#include "model_parameter.h"

/**
 * Model provides the base class for VTuber avatar/model.
 *
 * Models are rendered in viewports to make various means of projecting
 *  and rendering them in different contexts them easier.
 */
class Model : public godot::SubViewport {
    GDCLASS( Model, godot::SubViewport )

    void _on_property_updated( const godot::StringName &p_name, float p_value );

  protected:
    godot::TypedArray<ModelParameter> parameters;

    static void _bind_methods();

    void _add_model_parameter( const godot::Ref<ModelParameter> &p_parameter );

  public:
    Model() = default;

    [[nodiscard]] godot::TypedArray<ModelParameter> get_model_parameters() const;

    bool _set( const godot::StringName &p_name, const godot::Variant &p_value );
    bool _get( const godot::StringName &p_name, godot::Variant &r_ret ) const;
    bool _property_can_revert( const godot::StringName &p_name ) const;
    bool _property_get_revert( const godot::StringName &p_name, godot::Variant &r_property ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *p_list );

    /**
     * Returns a model bundle for the currently loaded model assets.
     *
     * Primarily intended for use with networked collaboration sessions.
     *
     * @return the packed model bundle.
     */
    virtual godot::Ref<ModelBundle> pack_bundle() {
        return {};
    };
};

#endif // VDOT_MODEL_H
