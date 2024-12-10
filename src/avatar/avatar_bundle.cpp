
#include "avatar_bundle.h"

void AvatarBundle::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "set_models", "models" ),
                                 &AvatarBundle::set_models );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_models" ), &AvatarBundle::get_models );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::ARRAY, "id", godot::PROPERTY_HINT_ARRAY_TYPE,
                                       ModelBundle::get_class_static() ),
                  "set_models", "get_models" );
}

AvatarBundle::AvatarBundle() = default;

AvatarBundle::~AvatarBundle() = default;

void AvatarBundle::set_models( const godot::TypedArray<godot::Ref<ModelBundle>> &p_models ) {
    models = p_models;
}

godot::TypedArray<godot::Ref<ModelBundle>> AvatarBundle::get_models() const {
    return models;
}
