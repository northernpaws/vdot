

#include "model_format.h"

void ModelFormat::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_loader_name" ),
                                 &ModelFormat::get_format_loader_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_loader_description" ),
                                 &ModelFormat::get_format_loader_description );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_recognized_extensions" ),
                                 &ModelFormat::get_recognized_extensions );
    godot::ClassDB::bind_method( godot::D_METHOD( "load_from_path" ),
                                 &ModelFormat::load_from_path );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_supported_formats" ),
                                 &ModelFormat::get_supported_formats );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_bundle_type" ),
                                 &ModelFormat::get_bundle_type );
    godot::ClassDB::bind_method( godot::D_METHOD( "create_from_bundle" ),
                                 &ModelFormat::create_from_bundle );
}
