
#include <godot_cpp/classes/zip_packer.hpp>
#include <godot_cpp/classes/zip_reader.hpp>

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/dir_access.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

#include "model_bundle.h"

void ModelBundle::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_format_type" ),
                                 &ModelBundle::get_format_type );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_format_type", "format" ),
                                 &ModelBundle::set_format_type );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING_NAME, "format_type" ),
                  "set_format_type", "get_format_type" );

    godot::ClassDB::bind_method( godot::D_METHOD( "add_directory", "path", "basepath", "recursive" ),
                                 &ModelBundle::add_directory );
    godot::ClassDB::bind_method( godot::D_METHOD( "add_file", "path", "basepath" ),
                                 &ModelBundle::set_format_type );

    godot::ClassDB::bind_method( godot::D_METHOD( "create_file", "path" ),
                                 &ModelBundle::create_file );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_file_data", "path", "data" ),
                                 &ModelBundle::set_file_data );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_file_data", "path" ),
                                 &ModelBundle::get_file_data );

//    godot::ClassDB::bind_method( godot::D_METHOD( "get_file_list" ),
//                                 &ModelBundle::get_file_list );

    godot::ClassDB::bind_method( godot::D_METHOD( "unpack_bundle", "target_path" ),
                                 &ModelBundle::unpack_bundle );
    godot::ClassDB::bind_method( godot::D_METHOD( "pack_bundle", "directory" ),
                                 &ModelBundle::pack_bundle );
}

void ModelBundle::set_format_type(const godot::StringName& p_format) {
    format_type = p_format;
}

godot::StringName ModelBundle::get_format_type() const {
    return format_type;
}

godot::Error ModelBundle::add_directory(const godot::String& p_path, const godot::String& p_basepath, bool p_recursive) {
    auto dir = godot::DirAccess::open(p_path);
    ERR_FAIL_COND_V_MSG(dir->get_open_error() != godot::OK, dir->get_open_error(), godot::vformat("Failed to open directory to add to model bundle: %s", p_path));

    dir->set_include_hidden(true);
    dir->set_include_navigational(false);

    auto dir_files = dir->get_files();
    for (const auto& filepath : dir_files) {
        auto err = add_file(p_path.path_join(filepath), p_basepath);
        ERR_FAIL_COND_V_MSG(err != godot::OK, err, godot::vformat("Error adding file from directory to model bundle: %s", p_path.path_join(filepath)));
    }

    if (p_recursive) {
        auto dir_directories = dir->get_directories();
        for (const auto& dirpath : dir_directories) {
            auto err = add_directory(p_path.path_join(dirpath), p_basepath, true);
            ERR_FAIL_COND_V_MSG(err != godot::OK, err, godot::vformat("Error adding directory to model bundle: %s", p_path.path_join(dirpath)));
        }
    }

    return godot::OK;
}

godot::Error ModelBundle::add_file(const godot::String& p_path, const godot::String& p_basepath) {
    auto file = godot::FileAccess::open(p_path, godot::FileAccess::ModeFlags::READ);
    ERR_FAIL_COND_V_MSG(file->get_open_error() != godot::OK, file->get_open_error(), "Failed to open file for reading.");

    BundleFile bundle_file;
    bundle_file.data = file->get_buffer(file->get_length());

    file->close();

    auto path = p_path.trim_prefix(p_basepath);

    files[path] = bundle_file;

    return godot::OK;
}

void ModelBundle::create_file(const godot::String& p_path) {
    ERR_FAIL_COND(files.has(p_path));

    files[p_path] = BundleFile();

    emit_changed();
    notify_property_list_changed();
}

void ModelBundle::set_file_data(const godot::String& p_path, const godot::PackedByteArray& p_data) {
    ERR_FAIL_COND_MSG(!files.has(p_path), godot::vformat("Specified file %s not found.", p_path));

    files[p_path].data = p_data;

    emit_changed();
}

godot::PackedByteArray ModelBundle::get_file_data(const godot::String& p_path) const {
    ERR_FAIL_COND_V_MSG(!files.has(p_path), {}, godot::vformat("Specified file %s not found.", p_path));

    return files[p_path].data;
}

godot::Vector<godot::String> ModelBundle::get_file_list() const {
    godot::Vector<godot::String> ret;
    ret.resize(files.size());

    int idx = 0;
    for (const godot::KeyValue<godot::String, BundleFile> &E : files) {
        ret.write[idx++] = E.key;
    }

    return ret;
}

bool ModelBundle::_set(const godot::StringName &p_name, const godot::Variant &p_property) {
    godot::String prop_name = p_name;
    if (prop_name.begins_with("file/")) {
        godot::String path = prop_name.get_slicec('/', 1);
        godot::String what = prop_name.get_slicec('/', 2);

        if (!files.has(path)) {
            create_file(path);
        }

        if (what == "data") {
            set_file_data(path, p_property);
        } else {
            return false;
        }

        return true;
    }

    return false;
}

bool ModelBundle::_get(const godot::StringName &p_name, godot::Variant &r_property) const {
    if (p_name.begins_with("file/")) {
        godot::String prop_name = p_name;
        godot::String path = prop_name.get_slicec( '/', 1 );
        ERR_FAIL_COND_V( !files.has( path ), false );
        godot::String what = prop_name.get_slicec( '/', 2 );

        if ( what == "data" ) {
            r_property = get_file_data( path );
        } else {
            return false;
        }

        return true;
    }

    return false;
}

void ModelBundle::_get_property_list(godot::List<godot::PropertyInfo> *p_list) const {
    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, "Bundle Files",
                                            godot::PROPERTY_HINT_NONE, "",
                                            godot::PROPERTY_USAGE_GROUP ) );

    for (const godot::KeyValue<godot::String, BundleFile> &file : files) {
        godot::String prop_name = vformat("%s/%s/", "file", file.key);
        p_list->push_back(godot::PropertyInfo(godot::Variant::PACKED_BYTE_ARRAY, prop_name + "data"));
    }
}

godot::Error ModelBundle::unpack_bundle( const godot::String &p_path ) {
    auto dir_access = godot::DirAccess::open(p_path);
    ERR_FAIL_COND_V_MSG(dir_access->get_open_error() != godot::OK, dir_access->get_open_error(), "Failed to open directory for writing.");

    for (const godot::KeyValue<godot::String, BundleFile> &bundled_file : files) {
        auto filepath = p_path.path_join(bundled_file.key);

        // Try to create the directory for containing the file.
        auto err = dir_access->make_dir_recursive(filepath.get_base_dir());
        ERR_FAIL_COND_V_MSG(err != godot::OK, err, "Failed to create directory for bundle un-packaging.");

        // Open and write the file to unpack.
        auto file_handle = godot::FileAccess::open(filepath, godot::FileAccess::ModeFlags::WRITE);
        ERR_FAIL_COND_V_MSG(file_handle->get_open_error() != godot::OK, file_handle->get_open_error(), "Failed to open file for writing.");
        file_handle->store_buffer(bundled_file.value.data);
        file_handle->close();
    }

    return godot::OK;
}

godot::Error ModelBundle::pack_bundle( const godot::String &p_path ) {
    return add_directory(p_path, p_path, true);
}
