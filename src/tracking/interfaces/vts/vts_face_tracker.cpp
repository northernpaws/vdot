
#include "vts_face_tracker.h"

void VTSFaceTracker::_bind_methods() {
}

VTSFaceTracker::VTSFaceTracker( const godot::String& p_address, uint32_t p_port ) {
    _address = p_address,
    _port = p_port;

    type = TrackingServer::TRACKER_FACE;
    name = godot::vformat("VTS %s:%d", _address, _port);
    description = godot::vformat("VTS face tracker on %s:%d", _address, _port);
}

VTSFaceTracker::~VTSFaceTracker() = default;
