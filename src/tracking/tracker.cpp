

#include "tracker.h"

void Tracker::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "get_tracker_name" ),
                                 &Tracker::get_tracker_name );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_tracker_description" ),
                                 &Tracker::get_tracker_description );
}

Tracker::Tracker() = default;

Tracker::~Tracker() = default;

godot::StringName Tracker::get_tracker_name() const {
    return tracker_name;
}

godot::StringName Tracker::get_tracker_description() const {
    return tracker_description;
}

TrackingServer::TrackerType Tracker::get_tracker_type() const {
    return tracker_type;
}