
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

#include "avatar_bundle.h"

void AvatarBundle::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "set_models", "models" ),
                                 &AvatarBundle::set_models );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_models" ), &AvatarBundle::get_models );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "id", godot::PROPERTY_HINT_ARRAY_TYPE,
                                       ModelBundle::get_class_static() ),
                  "set_models", "get_models" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_avatar_name", "name" ),
                                 &AvatarBundle::set_avatar_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_avatar_name" ),
                                 &AvatarBundle::get_avatar_name );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "name" ), "set_avatar_name",
                  "get_avatar_name" );
}

AvatarBundle::AvatarBundle() = default;

AvatarBundle::~AvatarBundle() = default;

godot::String AvatarBundle::get_avatar_name() const {
    return name;
}

void AvatarBundle::set_avatar_name( const godot::String &p_name ) {
    name = p_name;
}

void AvatarBundle::set_models( const godot::TypedArray<ModelBundle> &p_models ) {
    models = p_models;
}

godot::TypedArray<ModelBundle> AvatarBundle::get_models() const {
    return models;
}

void AvatarBundle::add_model( const godot::Ref<ModelBundle> &p_model ) {
    models.append( p_model );
}
