
#include <godot_cpp/classes/base_material3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/environment.hpp>
#include <godot_cpp/classes/h_split_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>

#include "godot_cpp/variant/callable.hpp"
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "../tracker_face.h"
#include "../tracking_interface.h"
#include "../tracking_server.h"

#include "trackers/face_tracker_panel.h"

#include "tracking_plugin_panel.h"

void TrackingPluginPanel::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_interface_added", "interface_name" ),
                                 &TrackingPluginPanel::_on_interface_added );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_interface_removed", "interface_name" ),
                                 &TrackingPluginPanel::_on_interface_removed );
    godot::ClassDB::bind_method(
        godot::D_METHOD( "_on_tracker_added", "tracker_name", "tacker_type" ),
        &TrackingPluginPanel::_on_tracker_added );
    godot::ClassDB::bind_method(
        godot::D_METHOD( "_on_tracker_removed", "tracker_name", "tacker_type" ),
        &TrackingPluginPanel::_on_tracker_removed );

    godot::ClassDB::bind_method( godot::D_METHOD( "_on_interface_selected", "index" ),
                                 &TrackingPluginPanel::_on_interface_selected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_tracker_selected", "index" ),
                                 &TrackingPluginPanel::_on_tracker_selected );
}

TrackingPluginPanel::TrackingPluginPanel() {
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_NULL_MSG( server, "Expected tracking server to be initialized." );

    server->connect( "interface_added", godot::Callable( this, "_on_interface_added" ) );
    server->connect( "interface_removed", godot::Callable( this, "_on_interface_removed" ) );
    server->connect( "tracker_added", godot::Callable( this, "_on_tracker_added" ) );
    server->connect( "tracker_removed", godot::Callable( this, "_on_tracker_removed" ) );

    // make panel fill vertical space.
    set_v_size_flags( SIZE_EXPAND_FILL );

    //    godot::ResourceLoader *res_loader = memnew( godot::ResourceLoader );

    {
        auto container = memnew( godot::HSplitContainer() );
        container->set_split_offset( 184 );
        container->set_anchors_preset( godot::Control::PRESET_FULL_RECT );

        {
            auto sidebar = memnew( godot::VBoxContainer );
            sidebar->set_v_size_flags( SIZE_EXPAND_FILL );

            {
                auto interface_container = memnew( godot::VBoxContainer );
                interface_container->set_v_size_flags( SIZE_EXPAND_FILL );

                auto interfaces_label = memnew( godot::Label );
                interfaces_label->set_text( "Tracking Interfaces" );
                interface_container->add_child( interfaces_label );

                _interface_list = memnew( godot::ItemList );
                _interface_list->set_v_size_flags( SIZE_EXPAND_FILL );
                _interface_list->connect( "item_selected", godot::Callable( this, "_on_interface_selected" ) );

                interface_container->add_child( _interface_list );
                sidebar->add_child( interface_container );
            }

            {
                auto tracker_container = memnew( godot::VBoxContainer );
                tracker_container->set_v_size_flags( SIZE_EXPAND_FILL );

                auto trackers_label = memnew( godot::Label );
                trackers_label->set_text( "Available Trackers" );
                tracker_container->add_child( trackers_label );

                _tracker_list = memnew( godot::ItemList );
                _tracker_list->set_v_size_flags( SIZE_EXPAND_FILL );
                _tracker_list->connect( "item_selected", godot::Callable( this, "_on_tracker_selected" ) );

                tracker_container->add_child( _tracker_list );
                sidebar->add_child( tracker_container );

                container->add_child( sidebar );
            }
        }

        {
            _main_container = memnew( godot::VBoxContainer );
            _main_container->set_v_size_flags( SIZE_EXPAND_FILL );

            container->add_child( _main_container );
        }
        add_child( container );
    }
}

TrackingPluginPanel::~TrackingPluginPanel() = default;

void TrackingPluginPanel::_enter_tree() {
    _update_interface_list();
    _update_tracker_list();
}

void TrackingPluginPanel::_process( double delta ) {
}

void TrackingPluginPanel::_update_interface_list() {
    _interface_list->clear();

    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_NULL_MSG( server, "Expected tracking server to be initialized." );

    for ( int i = 0; i < server->get_interfaces().size(); i++ ) {
        godot::Dictionary interface = server->get_interfaces()[i];
        godot::StringName name = interface["name"];

        auto idx = _interface_list->add_item( name );
        _interface_list->set_item_metadata( idx, name );
    }
}

void TrackingPluginPanel::_update_tracker_list() {
    _tracker_list->clear();

    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_NULL_MSG( server, "Expected tracking server to be initialized." );

    auto face_trackers = server->get_trackers( TrackingServer::TrackerType::TRACKER_FACE );
    for ( int i = 0; i < face_trackers.keys().size(); i++ ) {
        godot::StringName key = face_trackers.keys()[i];
        godot::Ref<FaceTracker> tracker = face_trackers[key];

        auto idx = _tracker_list->add_item( key );
        _tracker_list->set_item_metadata( idx, key );
    }
}

void TrackingPluginPanel::_on_interface_added( const godot::StringName &p_interface_name ) {
    auto idx = _interface_list->add_item( p_interface_name );
    _interface_list->set_item_metadata( idx, p_interface_name );
}

void TrackingPluginPanel::_on_interface_removed( const godot::StringName &p_interface_name ) {
    for ( int i = 0; i < _interface_list->get_item_count(); i++ ) {
        if ( _interface_list->get_item_metadata( i ) == p_interface_name ) {
            _interface_list->remove_item( i );
            break;
        }
    }
}

void TrackingPluginPanel::_on_tracker_added( const godot::StringName &p_tracker_name,
                                             TrackingServer::TrackerType p_tracker_type ) {
    auto idx = _tracker_list->add_item( p_tracker_name );
    _tracker_list->set_item_metadata( idx, p_tracker_name );
}

void TrackingPluginPanel::_on_tracker_removed( const godot::StringName &p_tracker_name,
                                               TrackingServer::TrackerType p_tracker_type ) {
    for ( int i = 0; i < _tracker_list->get_item_count(); i++ ) {
        if ( _tracker_list->get_item_metadata( i ) == p_tracker_name ) {
            _tracker_list->remove_item( i );
            break;
        }
    }
}

void TrackingPluginPanel::_on_interface_selected( int p_index ) {
    godot::StringName interface_name = _interface_list->get_item_metadata( p_index );

    TrackingServer *server = TrackingServer::get_singleton();

    auto interface = server->find_interface( interface_name );

    // TODO: add interface settings panel
}

void TrackingPluginPanel::_on_tracker_selected( int p_index ) {
    godot::StringName tracker_name = _tracker_list->get_item_metadata( p_index );

    TrackingServer *server = TrackingServer::get_singleton();

    auto tracker = server->get_tracker( tracker_name );

    if ( _main_container_item != nullptr ) {
        _main_container->remove_child( _main_container_item );
        _main_container_item->queue_free();
        _main_container_item = nullptr;
    }

    if ( tracker->get_tracker_type() == TrackingServer::TRACKER_FACE ) {
        auto tracker_panel = memnew( FaceTrackerPanel );
        tracker_panel->set_tracker( tracker );

        _main_container_item = tracker_panel;
    } else {
        ERR_FAIL_MSG( "Debugging panel not supported for tracker type." );
    }

    if ( _main_container_item != nullptr ) {
        _main_container->add_child( _main_container_item );
    }
}