

#include "tracking_interface.h"

void TrackingInterface::_bind_methods() {
    BIND_VIRTUAL_METHOD( TrackingInterface, get_name );

    BIND_VIRTUAL_METHOD( TrackingInterface, is_initialized );
    BIND_VIRTUAL_METHOD( TrackingInterface, initialize );
    BIND_VIRTUAL_METHOD( TrackingInterface, uninitialize );

    BIND_VIRTUAL_METHOD( TrackingInterface, process );
}

TrackingInterface::TrackingInterface() = default;

TrackingInterface::~TrackingInterface() = default;
