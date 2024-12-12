

#include "model_loader.h"
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

ModelLoader *ModelLoader::singleton = nullptr;

void ModelLoader::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_model_formats" ),
                                 &ModelLoader::get_model_formats );
    godot::ClassDB::bind_method( godot::D_METHOD( "add_model_format", "model_format" ),
                                 &ModelLoader::add_model_format );

    godot::ClassDB::bind_method( godot::D_METHOD( "find_format_by_path", "path" ),
                                 &ModelLoader::find_format_by_path );
    godot::ClassDB::bind_method( godot::D_METHOD( "load_from_path", "path" ),
                                 &ModelLoader::load_from_path );
    godot::ClassDB::bind_method( godot::D_METHOD( "find_format", "format_name" ),
                                 &ModelLoader::find_format );
    godot::ClassDB::bind_method( godot::D_METHOD( "load_bundle", "bundle_path" ),
                                 &ModelLoader::load_bundle );
    godot::ClassDB::bind_method( godot::D_METHOD( "create_from_bundle", "model_bundle" ),
                                 &ModelLoader::create_from_bundle );
}

ModelLoader::ModelLoader() {
    singleton = this;
}

godot::TypedArray<ModelFormat> ModelLoader::get_model_formats() const {
    return formats;
}

void ModelLoader::add_model_format( const godot::Ref<ModelFormat> &p_format ) {
    formats.push_back( p_format );
}

godot::Ref<ModelFormat> ModelLoader::find_format_by_path( const godot::String &p_path ) const {
    godot::Ref<ModelFormat> ret = nullptr;

    for ( int i = 0; i < formats.size(); i++ ) {
        godot::Ref<ModelFormat> format = formats[i];

        auto recognized_extensions = format->get_recognized_extensions();
        for ( const auto &extension : recognized_extensions ) {
            if ( extension == p_path.get_extension() ) {
                ret = format;
                break;
            }
        }

        if ( format->can_handle_path( p_path ) ) {
            ret = format;
            break;
        }

        if ( ret.is_valid() ) {
            break;
        }
    }

    return ret;
}

Model *ModelLoader::load_from_path( const godot::String &p_path ) const {
    godot::Ref<ModelFormat> model_format = find_format_by_path( p_path );
    ERR_FAIL_COND_V_MSG( !model_format.is_valid(), nullptr,
                         godot::vformat( "Couldn't find model format for extension '%s'.",
                                         p_path.get_extension() ) );

    auto model = model_format->load_from_path( p_path );
    ERR_FAIL_COND_V_MSG( model == nullptr, nullptr, "Failed to load model from path." );

    return model;
}

godot::Ref<ModelFormat> ModelLoader::find_format( const godot::String &p_format ) const {
    godot::Ref<ModelFormat> bundle_format = nullptr;

    for ( int i = 0; i < formats.size(); i++ ) {
        godot::Ref<ModelFormat> format = formats[i];

        auto supported_formats = format->get_supported_formats();
        for ( const auto &format_name : supported_formats ) {
            if ( format_name == p_format ) {
                bundle_format = format;
                break;
            }
        }

        if ( bundle_format.is_valid() ) {
            break;
        }
    }

    return bundle_format;
}

godot::Ref<ModelBundle> ModelLoader::load_bundle( const godot::String &p_path ) const {
    auto res_loader = godot::ResourceLoader::get_singleton();

    // TODO: how can we optimize this to avoid loading the bundle twice?

    // First, load the bundle as a generic bundle.
    godot::Ref<ModelBundle> bundle = res_loader->load( p_path, ModelBundle::get_class_static() );

    // Find the specific model format handle for the bundle format.
    godot::Ref<ModelFormat> bundle_format = find_format( bundle->get_format_type() );
    ERR_FAIL_COND_V_MSG( !bundle_format.is_valid(), nullptr,
                         "Couldn't find model format to load bundle." );

    // Now, load the bundle as the actual type.
    bundle = res_loader->load( p_path, bundle_format->get_bundle_type() );

    return bundle;
}

Model *ModelLoader::create_from_bundle( const godot::Ref<ModelBundle> &p_bundle ) const {
    auto hash = p_bundle->compute_hash();
    godot::String bundle_extract_path = godot::String( BUNDLE_EXTRACT_BASE_PATH ).path_join( hash );
    auto dir = godot::DirAccess::open( bundle_extract_path );

    if ( !dir->dir_exists( "" ) ) {
        // Make the extraction direction
        auto err = dir->make_dir_recursive( "" );
        ERR_FAIL_COND_V_MSG( err, nullptr, "Failed to create bundle extraction directory." );
    } else {
        // TODO: actually handle this properly
        ERR_FAIL_V_MSG( nullptr, "Bundle directory already exists" );
    }

    godot::Ref<ModelFormat> bundle_format = find_format( p_bundle->get_format_type() );
    ERR_FAIL_COND_V_MSG( !bundle_format.is_valid(), nullptr,
                         "Couldn't find model format to load bundle." );

    auto model = bundle_format->create_from_bundle( p_bundle, bundle_extract_path );
    ERR_FAIL_COND_V_MSG( model == nullptr, nullptr, "Failed to create model from bundle." );

    return model;
}