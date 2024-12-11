
#include <CubismModelSettingJson.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include "live2d_model_bundle.h"
#include "live2d_model_format.h"

void Live2DModelFormat::_bind_methods() {
}

Live2DModelFormat::Live2DModelFormat() {
    format_type = "live2d";
}

godot::Ref<ModelBundle> Live2DModelFormat::load_model( const godot::String &p_path ) const {
    ERR_FAIL_COND_V_MSG( p_path.get_extension() != ".model3.json", nullptr,
                         "Live2DModelFormat expected a .model3.json file as the input." );

    godot::Ref<Live2DModelBundle> bundle;
    bundle.instantiate();

    return bundle;
}

godot::Ref<ModelBundle> Live2DModelFormat::import_model( const godot::String &p_path ) const {
    ERR_FAIL_COND_V_MSG( p_path.get_extension() != ".model3.json", nullptr,
                         "Live2DModelFormat expected a .model3.json file as the input." );

    godot::Ref<Live2DModelBundle> bundle;
    bundle.instantiate();

    auto target_path = get_model_directory_path( "unnamed" ); // TODO: pass model name

    godot::Vector<godot::String> paths;

    // Read in the .model3.json settings manifest file.
    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( p_path );
    ERR_FAIL_COND_V_MSG( buffer.size() == 0, nullptr, "Failed to read file: zero bytes." );

    // Decode the model settings from the buffer.
    auto model_settings = CSM_NEW Live2D::Cubism::Framework::CubismModelSettingJson(
        buffer.ptr(), static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );

    godot::String gd_filename;
    gd_filename.parse_utf8( model_settings->GetModelFileName() );
    godot::String moc3_pathname = p_path.get_base_dir().path_join( gd_filename );

    // Read the moc3 file.
    buffer = godot::FileAccess::get_file_as_bytes( moc3_pathname );

    return bundle;
}
