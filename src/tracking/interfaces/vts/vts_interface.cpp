#include <godot_cpp/variant/utility_functions.hpp>

#include "../../tracking_server.h"

#include "vts_face_tracker.h"
#include "vts_interface.h"

VTSInterface* VTSInterface::singleton = nullptr;


VTSInterface* VTSInterface::get_singleton() {
    return singleton;
}

void VTSInterface::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "initialize" ),
                                 &VTSInterface::initialize );
    godot::ClassDB::bind_method( godot::D_METHOD( "uninitialize" ),
                                 &VTSInterface::uninitialize );
    godot::ClassDB::bind_method( godot::D_METHOD( "is_initialized" ),
                                 &VTSInterface::is_initialized );

    godot::ClassDB::bind_method( godot::D_METHOD( "register_tracker", "address", "port" ),
                                 &VTSInterface::register_tracker );
}

VTSInterface::VTSInterface() {
    singleton = this;
}

VTSInterface::~VTSInterface() {
    _trackers.clear();
}

bool VTSInterface::is_initialized() {
    return _initialized;
}

bool VTSInterface::initialize() {
    // TODO: initialize

    godot::UtilityFunctions::print( "Initialized VTS facial tracking interface" );

    _initialized = true;

    return _initialized;
}

void VTSInterface::uninitialize() {
    // TODO: uninitialize

    _trackers.clear();

    _initialized = false;

    godot::UtilityFunctions::print( "Shut down VTS facial tracking interface" );
}

void VTSInterface::process() {
}

godot::Ref<VTSFaceTracker> VTSInterface::register_tracker(const godot::String& address, uint16_t port) {
    ERR_FAIL_COND_V_MSG(_initialized == false, nullptr, "VTS Interface needs to be initialized.");

    godot::Ref<VTSFaceTracker> tracker = memnew(VTSFaceTracker);

    // Add the tracker to the tracker dictionary.
    _trackers[tracker->get_tracker_name()] = tracker;

    // Register the tracker with the tracking server.
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_NULL_V_MSG(server, nullptr, "Expected tracking server to be initialized to register VTS tracker.");
    server->add_tracker( tracker );

    return tracker;
}