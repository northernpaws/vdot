

#include "avatar_manager.h"

void AvatarType::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_type_name" ),
                                 &AvatarType::get_avatar_type_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_type_name", "avatar_type_name" ),
                                 &AvatarType::set_avatar_type_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "avatar_type_name"),
                  "set_avatar_type_name", "get_avatar_type_name" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_type_description" ),
                                 &AvatarType::get_avatar_type_description );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_type_description", "avatar_type_description" ),
                                 &AvatarType::set_avatar_type_description );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "avatar_type_description" ),
                  "set_avatar_type_description", "get_avatar_type_description" );
}

godot::String AvatarType::get_avatar_type_name() const {
    return name;
}

void AvatarType::set_avatar_type_name(const godot::String& p_name) {
    name = p_name;
}

godot::String AvatarType::get_avatar_type_description() const {
    return description;
}

void AvatarType::set_avatar_type_description(const godot::String& p_description) {
    description = p_description;
}

void AvatarManager::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_types" ),
                                 &AvatarManager::get_avatar_types );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_types", "avatar_type_name" ),
                                 &AvatarManager::set_avatar_types );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "avatar_types",
                                       godot::PROPERTY_HINT_TYPE_STRING,
                                       godot::String::num(godot::Variant::OBJECT) + "/" + godot::String::num(godot::PROPERTY_HINT_RESOURCE_TYPE) + ":" + AvatarType::get_class_static()),
                  "set_avatar_types", "get_avatar_types" );
}

void AvatarManager::set_avatar_types(const godot::TypedArray<AvatarType>& p_types)  {
    avatar_types = p_types;
}

godot::TypedArray<AvatarType> AvatarManager::get_avatar_types() const {
    return avatar_types;
}
