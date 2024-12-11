
#include <CubismFramework.hpp>
#include <CubismModelSettingJson.hpp>

#include <godot_cpp/classes/file_access.hpp>

#include "live2d_model_bundle.h"

void Live2DModelBundle::_bind_methods() {
}

godot::Error Live2DModelBundle::pack_from_model3( const godot::String &p_path ) {
    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( p_path );
    ERR_FAIL_COND_V_MSG( buffer.size() == 0, godot::FAILED,
                         godot::vformat( "Failed to read file: %s", p_path ) );

    auto model_setting = CSM_NEW Live2D::Cubism::Framework::CubismModelSettingJson(
        buffer.ptr(), static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );

    // Successful read, add the .model3.json file to the bundle
    auto err = add_file( p_path, p_path.get_base_dir() );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack .model3.json" );

    // Derive the moc3 file path
    godot::String gd_filename;
    gd_filename.parse_utf8( model_setting->GetModelFileName() );
    err = add_file( p_path.get_base_dir().path_join( gd_filename ), p_path.get_base_dir() );
    ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack .moc3" );

    if ( strcmp( model_setting->GetPhysicsFileName(), "" ) != 0 ) {
        godot::String phys_filename;
        phys_filename.parse_utf8( model_setting->GetPhysicsFileName() );
        err = add_file( p_path.get_base_dir().path_join( phys_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack .physics3.json" );
    }

    if ( strcmp( model_setting->GetPoseFileName(), "" ) != 0 ) {
        godot::String pose_filename;
        pose_filename.parse_utf8( model_setting->GetPoseFileName() );
        err = add_file( p_path.get_base_dir().path_join( pose_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack .pose3.json" );
    }

    if ( strcmp( model_setting->GetDisplayInfoFileName(), "" ) != 0 ) {
        godot::String info_filename;
        info_filename.parse_utf8( model_setting->GetDisplayInfoFileName() );
        err = add_file( p_path.get_base_dir().path_join( info_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack display info file" );
    }

    if ( strcmp( model_setting->GetUserDataFile(), "" ) != 0 ) {
        godot::String userdata_filename;
        userdata_filename.parse_utf8( model_setting->GetUserDataFile() );
        err =
            add_file( p_path.get_base_dir().path_join( userdata_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err, "Failed to pack userdata filename" );
    }

    for ( int i = 0; i < model_setting->GetTextureCount(); i++ ) {
        if ( strcmp( model_setting->GetTextureFileName( i ), "" ) == 0 ) {
            continue;
        }

        godot::String tex_filename;
        tex_filename.parse_utf8( model_setting->GetTextureFileName( i ) );
        err = add_file( p_path.get_base_dir().path_join( tex_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err,
                             godot::vformat( "Failed to pack texture: %s", tex_filename ) );
    }

    for ( int i = 0; i < model_setting->GetExpressionCount(); i++ ) {
        if ( strcmp( model_setting->GetExpressionFileName( i ), "" ) == 0 ) {
            continue;
        }

        godot::String exp_filename;
        exp_filename.parse_utf8( model_setting->GetExpressionFileName( i ) );
        err = add_file( p_path.get_base_dir().path_join( exp_filename ), p_path.get_base_dir() );
        ERR_FAIL_COND_V_MSG( err != godot::OK, err,
                             godot::vformat( "Failed to pack expression: %s", exp_filename ) );
    }

    for ( int i = 0; i < model_setting->GetMotionGroupCount(); i++ ) {
        if ( strcmp( model_setting->GetMotionGroupName( i ), "" ) == 0 ) {
            continue;
        }

        auto group_name = model_setting->GetMotionGroupName( i );

        for ( int x = 0; x < model_setting->GetMotionCount( group_name ); x++ ) {
            if ( strcmp( model_setting->GetMotionFileName( group_name, x ), "" ) == 0 ) {
                continue;
            }
            godot::String motion_filename;
            motion_filename.parse_utf8( model_setting->GetMotionFileName( group_name, x ) );
            err = add_file( p_path.get_base_dir().path_join( motion_filename ),
                            p_path.get_base_dir() );
            ERR_FAIL_COND_V_MSG( err != godot::OK, err,
                                 godot::vformat( "Failed to pack motion: %s", motion_filename ) );
        }
    }

    return godot::OK;
}