
#include "model_2d.h"

void Model2D::_bind_methods() {
}

bool Model2D::_set( const godot::StringName &p_name, const godot::Variant &p_value ) {
    return Model::_set( p_name, p_value );
}

bool Model2D::_get( const godot::StringName &p_name, godot::Variant &r_ret ) const {
    return Model::_get( p_name, r_ret );
}

bool Model2D::_property_can_revert( const godot::StringName &p_name ) const {
    return Model::_property_can_revert( p_name );
}

bool Model2D::_property_get_revert( const godot::StringName &p_name,
                                    godot::Variant &r_property ) const {
    return Model::_property_get_revert( p_name, r_property );
}

void Model2D::_get_property_list( godot::List<godot::PropertyInfo> *p_list ) {
    Model::_get_property_list( p_list );
}