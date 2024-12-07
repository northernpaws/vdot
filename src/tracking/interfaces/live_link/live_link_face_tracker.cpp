

#include "live_link_face_tracker.h"

void LiveLinkFaceTracker::_bind_methods() {
}

LiveLinkFaceTracker::LiveLinkFaceTracker( const godot::Ref<LiveLinkClient> &p_client ) {
    _client = p_client;

    type = TrackingServer::TRACKER_FACE;
    name = tracker_name( _client );
    description = godot::vformat( "LiveLink face tracker %s (%s).", _client->_name, _client->_id );
}

LiveLinkFaceTracker::~LiveLinkFaceTracker() = default;

godot::StringName LiveLinkFaceTracker::tracker_name( const godot::Ref<LiveLinkClient> &client ) {
    return godot::vformat( "/user/face/%s", client->_name );
}