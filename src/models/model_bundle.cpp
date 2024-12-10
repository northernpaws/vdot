
#include "model_bundle.h"

void ModelBundle::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_type" ),
                                 &ModelBundle::get_format_type );
}

godot::StringName ModelBundle::get_format_type() const {
    return format_type;
}