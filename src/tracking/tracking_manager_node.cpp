
#include <godot_cpp/variant/utility_functions.hpp>

#include "tracking_server.h"

#include "tracking_manager_node.h"

void TrackingManagerNode::_bind_methods() {
}

void TrackingManagerNode::_enter_tree() {
    godot::UtilityFunctions::push_warning(
        "The TrackingManagerNode is a temporary solutions while we're exploring better options for "
        "syncing the tracking process loop with the main loop." );
}

void TrackingManagerNode::_process( double p_delta ) {
    TrackingServer::get_singleton()->_process();
}

godot::PackedStringArray TrackingManagerNode::_get_configuration_warnings() const {
    godot::PackedStringArray ary;

    ary.push_back( "This is a temporary solutions while we figure out a better method for hooking "
                   "into the process loop." );

    return ary;
}