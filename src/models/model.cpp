
#include "model.h"

void Model::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_model_parameters" ),
                                 &Model::get_model_parameters );
}

godot::Array Model::get_model_parameters() const {
    return parameters;
}