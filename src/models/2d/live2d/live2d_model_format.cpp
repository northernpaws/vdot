
#include "cubism_model.h"
#include "live2d_model_bundle.h"

#include "live2d_model_format.h"

void Live2DModelFormat::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_loader_name" ),
                                 &Live2DModelFormat::get_format_loader_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_loader_description" ),
                                 &Live2DModelFormat::get_format_loader_description );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_recognized_extensions" ),
                                 &Live2DModelFormat::get_recognized_extensions );
    godot::ClassDB::bind_method( godot::D_METHOD( "load_from_path" ),
                                 &Live2DModelFormat::load_from_path );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_supported_formats" ),
                                 &Live2DModelFormat::get_supported_formats );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_bundle_type" ),
                                 &Live2DModelFormat::get_bundle_type );
    godot::ClassDB::bind_method( godot::D_METHOD( "create_from_bundle" ),
                                 &Live2DModelFormat::create_from_bundle );
}

godot::PackedStringArray Live2DModelFormat::get_recognized_extensions() const {
    godot::PackedStringArray extensions;

    extensions.push_back("model3.json");

    return extensions;
}

Model* Live2DModelFormat::load_from_path(const godot::String& p_path) const {
    ERR_FAIL_COND_V_MSG(p_path.get_extension() != "model3.json", nullptr,
                         godot::vformat("Expected model3.json filepath, got %s", p_path.get_extension()));

    CubismModel* model = memnew(CubismModel);

    // Load the model assets from the model3 file.
    model->set_assets(p_path);

    return model;
}

godot::PackedStringArray Live2DModelFormat::get_supported_formats() const {
    godot::PackedStringArray formats;

    formats.push_back("live2d");

    return formats;
}

godot::String Live2DModelFormat::get_bundle_type() const {
    return Live2DModelBundle::get_class_static();
}

Model* Live2DModelFormat::create_from_bundle(const godot::Ref<ModelBundle>& p_bundle, const godot::String& p_extract_path) {
    ERR_FAIL_COND_V_MSG(p_bundle->get_format_type() != godot::StringName("live2d"), nullptr,
                         godot::vformat("Live2DModelFormat cannot handle the format '%s'", p_bundle->get_format_type()));
    ERR_FAIL_COND_V_MSG(p_bundle->get_class() != Live2DModelBundle::get_class_static(), nullptr,
                         godot::vformat("Live2DModelFormat got unexpected resource type '%s'", p_bundle->get_class()));

    godot::Ref<Live2DModelBundle> bundle = p_bundle;

    auto err = bundle->unpack_bundle(p_extract_path);
    ERR_FAIL_COND_V_MSG(err, nullptr, "Failed to extract model bundle.");

    // Load the model assets from the model3 file embedded in the bundle.
    return load_from_path(p_extract_path.path_join(bundle->get_model3_path()));
}
