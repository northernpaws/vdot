
#include <godot_cpp/core/class_db.hpp>

#include "model_format.h"

void ModelFormat::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_type" ),
                                 &ModelFormat::get_format_type );
}

godot::String ModelFormat::get_model_directory_path( const godot::String &p_name ){
    return godot::vformat( "user://bundles/models/%s", p_name )
}

godot::StringName ModelFormat::get_format_type() const {
    return format_type;
}