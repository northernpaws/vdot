

#include "avatar.h"

void Avatar::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_parameters" ),
                                 &Avatar::get_avatar_parameters );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_parameters", "parameters" ),
                                 &Avatar::set_avatar_parameters );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "parameters",
                                       godot::PROPERTY_HINT_TYPE_STRING,
                                       godot::String::num(godot::Variant::OBJECT) + "/" + godot::String::num(godot::PROPERTY_HINT_RESOURCE_TYPE) + ":" + AvatarParameter::get_class_static() ),
                  "set_avatar_parameters", "get_avatar_parameters" );
}

godot::TypedArray<godot::Ref<AvatarParameter>> Avatar::get_avatar_parameters() const {
    return parameters;
}

void Avatar::set_avatar_parameters( const godot::TypedArray<godot::Ref<AvatarParameter>> &p_parameters ) {
    parameters = p_parameters;
}
