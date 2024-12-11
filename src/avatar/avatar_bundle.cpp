
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
}

AvatarBundle::AvatarBundle() = default;

AvatarBundle::~AvatarBundle() = default;

void AvatarBundle::set_models( const godot::TypedArray<godot::Ref<ModelBundle>> &p_models ) {
    models = p_models;
}

godot::TypedArray<godot::Ref<ModelBundle>> AvatarBundle::get_models() const {
    return models;
}

godot::Error AvatarBundle::compress() {
    // ====================
    // Directory Setup

    godot::String base_path = godot::vformat( "user://bundles/avatars/%s", name );
    auto fs = godot::DirAccess::open( base_path );
    auto err = fs->make_dir( "/" );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to make avatar bundle directory." );

    // ====================
    // Model saving

    auto models_fs = fs->open( "/models" );
    err = models_fs->make_dir( "/" );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to make avatar bundle modules directory." );

    // TODO: save models to bundle dir

    // ====================
    // Avatar Saving

    auto saver = godot::ResourceSaver::get_singleton();

    err = saver->save( this, fs->get_current_dir( true ).path_join( "avatar.tres" ),
                       godot::ResourceSaver::SaverFlags::FLAG_REPLACE_SUBRESOURCE_PATHS );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to save avatar manifest." );

    // ====================
    // Compression

    return godot::OK;
}