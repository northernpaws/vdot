
#include "tracking_interface.h"
#include <godot_cpp/variant/utility_functions.hpp>

#include "tracker.h"
#include "tracking_server.h"

TrackingServer *TrackingServer::singleton = nullptr;

void TrackingServer::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_interface", "index" ),
                                 &TrackingServer::get_interface );
    godot::ClassDB::bind_method( godot::D_METHOD( "find_interface", "name" ),
                                 &TrackingServer::find_interface );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_interfaces" ),
                                 &TrackingServer::get_interfaces );

    godot::ClassDB::bind_method( godot::D_METHOD( "add_tracker", "tracker" ),
                                 &TrackingServer::add_tracker );
    godot::ClassDB::bind_method( godot::D_METHOD( "remove_tracker", "tracker" ),
                                 &TrackingServer::remove_tracker );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_trackers", "tracker_types" ),
                                 &TrackingServer::get_trackers );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_tracker", "tracker_name" ),
                                 &TrackingServer::get_tracker );

    godot::ClassDB::bind_method( godot::D_METHOD( "_process" ), &TrackingServer::_process );

    BIND_ENUM_CONSTANT( TRACKER_FACE );
    BIND_ENUM_CONSTANT( TRACKER_UNKNOWN );

    ADD_SIGNAL( godot::MethodInfo(
        "interface_added", godot::PropertyInfo( godot::Variant::STRING_NAME, "interface_name" ) ) );
    ADD_SIGNAL(
        godot::MethodInfo( "interface_removed",
                           godot::PropertyInfo( godot::Variant::STRING_NAME, "interface_name" ) ) );

    ADD_SIGNAL( godot::MethodInfo(
        "tracker_added", godot::PropertyInfo( godot::Variant::STRING_NAME, "tracker_name" ),
        godot::PropertyInfo( godot::Variant::INT, "type" ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "tracker_updated", godot::PropertyInfo( godot::Variant::STRING_NAME, "tracker_name" ),
        godot::PropertyInfo( godot::Variant::INT, "type" ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "tracker_removed", godot::PropertyInfo( godot::Variant::STRING_NAME, "tracker_name" ),
        godot::PropertyInfo( godot::Variant::INT, "type" ) ) );
}

TrackingServer *TrackingServer::get_singleton() {
    return singleton;
}

TrackingServer::TrackingServer() {
    singleton = this;
}

TrackingServer::~TrackingServer() {
    singleton = nullptr;
}

void TrackingServer::_notification( int p_what ) {
    if ( p_what == NOTIFICATION_POSTINITIALIZE ) {
    }
}

void TrackingServer::_process() {
    for ( int i = 0; i < _interfaces.size(); i++ ) {
        if ( !_interfaces[i].is_valid() ) {
            // ignore, not a valid reference
        } else if ( _interfaces[i]->is_initialized() ) {
            _interfaces.write[i]->process();
        }
    }
}

void TrackingServer::add_interface( const godot::Ref<TrackingInterface> &p_interface ) {
    ERR_FAIL_COND( p_interface.is_null() );

    for ( int i = 0; i < _interfaces.size(); i++ ) {
        if ( _interfaces[i] == p_interface ) {
            ERR_PRINT( "Interface was already added" );
            return;
        }
    }

    _interfaces.append( p_interface );
    emit_signal( "interface_added", p_interface->get_name() );
}

void TrackingServer::remove_interface( const godot::Ref<TrackingInterface> &p_interface ) {
    ERR_FAIL_COND( p_interface.is_null() );

    int idx = -1;
    for ( int i = 0; i < _interfaces.size(); i++ ) {
        if ( _interfaces[i] == p_interface ) {
            idx = i;
            break;
        }
    }

    ERR_FAIL_COND_MSG( idx == -1, "Interface not found." );
    godot::UtilityFunctions::print( "Tracking: Removed interface \"" + p_interface->get_name() +
                                    "\"" );
    emit_signal( "interface_removed", p_interface->get_name() );
    _interfaces.remove_at( idx );
}

int TrackingServer::get_interface_count() const {
    return static_cast<int>( _interfaces.size() );
}

godot::Ref<TrackingInterface> TrackingServer::get_interface( int p_index ) const {
    ERR_FAIL_INDEX_V( p_index, _interfaces.size(), nullptr );

    return _interfaces[p_index];
}

godot::Ref<TrackingInterface> TrackingServer::find_interface( const godot::String &p_name ) const {
    for ( const auto &_interface : _interfaces ) {
        if ( _interface->get_name() == p_name ) {
            return _interface;
        }
    }

    return {};
}

godot::TypedArray<godot::Dictionary> TrackingServer::get_interfaces() const {
    godot::Array ret;

    for ( int i = 0; i < _interfaces.size(); i++ ) {
        godot::Dictionary iface_info;

        iface_info["id"] = i;
        iface_info["name"] = _interfaces[i]->get_name();

        ret.push_back( iface_info );
    }

    return ret;
}

void TrackingServer::add_tracker( const godot::Ref<Tracker> &p_tracker ) {
    ERR_FAIL_COND( p_tracker.is_null() );

    godot::StringName tracker_name = p_tracker->get_tracker_name();
    if ( _trackers.has( tracker_name ) ) {
        if ( _trackers[tracker_name] != p_tracker ) {
            // We already have a tracker with this name, we're going to replace it
            _trackers[tracker_name] = p_tracker;
            emit_signal( "tracker_updated", tracker_name, p_tracker->get_tracker_type() );
        }
    } else {
        _trackers[tracker_name] = p_tracker;
        emit_signal( "tracker_added", tracker_name, p_tracker->get_tracker_type() );
    }
}

void TrackingServer::remove_tracker( const godot::Ref<Tracker> &p_tracker ) {
    ERR_FAIL_COND( p_tracker.is_null() );

    godot::StringName tracker_name = p_tracker->get_tracker_name();
    if ( _trackers.has( tracker_name ) ) {
        // we send the signal right before removing it
        emit_signal( "tracker_removed", p_tracker->get_tracker_name(),
                     p_tracker->get_tracker_type() );

        // and remove it
        _trackers.erase( tracker_name );
    }
}

godot::Dictionary TrackingServer::get_trackers( TrackerType p_tracker_types ) {
    godot::Dictionary res;

    for ( int i = 0; i < _trackers.keys().size(); i++ ) {
        auto key = _trackers.keys()[i];
        godot::Ref<Tracker> tracker = _trackers[key];

        if ( tracker.is_valid() && ( tracker->get_tracker_type() & p_tracker_types ) != 0 ) {
            res[tracker->get_tracker_name()] = tracker;
        }
    }

    return res;
}

godot::Ref<Tracker> TrackingServer::get_tracker( const godot::StringName &p_name ) const {
    if ( _trackers.has( p_name ) ) {
        return _trackers[p_name];
    } else {
        return {};
    }
}
