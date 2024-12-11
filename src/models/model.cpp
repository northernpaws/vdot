
#include "model.h"
#include "model_parameter.h"

void Model::_on_property_updated( const godot::StringName &p_name, float p_value ) {
    notify_property_list_changed();
}

void Model::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_model_parameters" ),
                                 &Model::get_model_parameters );
    ADD_PROPERTY( godot::PropertyInfo(
                      godot::Variant::ARRAY, "model_parameters", godot::PROPERTY_HINT_TYPE_STRING,
                      godot::String::num( godot::Variant::OBJECT ) + "/" +
                          godot::String::num( godot::PROPERTY_HINT_RESOURCE_TYPE ) + ":" +
                          ModelParameter::get_class_static(),
                      godot::PROPERTY_USAGE_READ_ONLY | godot::PROPERTY_USAGE_EDITOR ),
                  godot::String(), "get_model_parameters" );

    godot::ClassDB::bind_method( godot::D_METHOD( "_on_property_updated" ),
                                 &Model::_on_property_updated );
}

void Model::_add_model_parameter( const godot::Ref<ModelParameter> &p_parameter ) {
    parameters.append( p_parameter );

    p_parameter->connect( "value_updated", godot::Callable( this, "_on_property_updated" ) );
}

godot::TypedArray<ModelParameter> Model::get_model_parameters() const {
    return parameters;
}

bool Model::_set( const godot::StringName &p_name, const godot::Variant &p_value ) {
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<ModelParameter> parameter = parameters[i];

        if ( p_name == parameter->get_parameter_id() ) {
            parameter->set_parameter_value( p_value );
            return true;
        }
    }

    return false;
}

bool Model::_get( const godot::StringName &p_name, godot::Variant &r_ret ) const {
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<ModelParameter> parameter = parameters[i];

        if ( p_name == parameter->get_parameter_id() ) {
            r_ret = parameter->get_parameter_value();
            return true;
        }
    }

    return false;
}

bool Model::_property_can_revert( const godot::StringName &p_name ) const {
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<ModelParameter> parameter = parameters[i];

        if ( p_name == parameter->get_parameter_id() ) {
            return true;
        }
    }

    return false;
}

bool Model::_property_get_revert( const godot::StringName &p_name,
                                  godot::Variant &r_property ) const {
    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<ModelParameter> parameter = parameters[i];

        if ( p_name == parameter->get_parameter_id() ) {
            r_property = parameter->get_parameter_default_value();
            return true;
        }
    }

    return false;
}

void Model::_get_property_list( godot::List<godot::PropertyInfo> *p_list ) {

    // ====================
    // Model Parameters

    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, "Parameters",
                                            godot::PROPERTY_HINT_NONE, "",
                                            godot::PROPERTY_USAGE_GROUP ) );

    for ( int i = 0; i < parameters.size(); i++ ) {
        godot::Ref<ModelParameter> parameter = parameters[i];

        godot::Array ary_value;
        ary_value.append( parameter->get_parameter_minimum_value() );
        ary_value.append( parameter->get_parameter_maximum_value() );

        godot::PropertyInfo pinfo(
            godot::Variant::FLOAT, parameter->get_parameter_id(), godot::PROPERTY_HINT_RANGE,
            godot::String( "{0},{1}" ).format( ary_value ), godot::PROPERTY_USAGE_DEFAULT );

        p_list->push_back( pinfo );
    }
}
