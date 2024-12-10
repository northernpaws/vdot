

#ifndef VDOT_MODEL_2D_H
#define VDOT_MODEL_2D_H

#include "models/model.h"

/**
 * The base class for 2D-based VTuber models.
 */
class Model2D : public Model {
    GDCLASS( Model2D, Model )
  protected:
    static void _bind_methods();

  public:
    Model2D() = default;

    bool _set( const godot::StringName &p_name, const godot::Variant &p_value );
    bool _get( const godot::StringName &p_name, godot::Variant &r_ret ) const;
    bool _property_can_revert( const godot::StringName &p_name ) const;
    bool _property_get_revert( const godot::StringName &p_name, godot::Variant &r_property ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *p_list );
};

#endif // VDOT_MODEL_2D_H
