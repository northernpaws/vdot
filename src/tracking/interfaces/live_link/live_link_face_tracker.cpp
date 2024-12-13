

#include "live_link_face_tracker.h"

void LiveLinkFaceTracker::_bind_methods() {
}

LiveLinkFaceTracker::LiveLinkFaceTracker( const godot::Ref<LiveLinkClient> &p_client ) {
    _client = p_client;

    tracker_type = TrackingServer::TRACKER_FACE;
    tracker_name = _tracker_name( _client );
    tracker_description =
        godot::vformat( "LiveLink face tracker %s (%s).", _client->_name, _client->_id );
}

LiveLinkFaceTracker::~LiveLinkFaceTracker() = default;

godot::StringName LiveLinkFaceTracker::_tracker_name( const godot::Ref<LiveLinkClient> &client ) {
    return client->_name;
}