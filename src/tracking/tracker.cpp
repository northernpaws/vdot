

#include "tracker.h"

void Tracker::_bind_methods() {
}

Tracker::Tracker() {
}

Tracker::~Tracker() {
}

godot::StringName Tracker::get_tracker_name() const {
    return name;
}

godot::StringName Tracker::get_tracker_description() const {
    return description;
}

TrackingServer::TrackerType Tracker::get_tracker_type() const {
    return type;
}