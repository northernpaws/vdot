
#ifndef VDOT_TRACKER_H
#define VDOT_TRACKER_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "tracking_server.h"

/**
 * Base class for implementing head, face, and body trackers.
 */
class Tracker : public godot::RefCounted {
    GDCLASS( Tracker, godot::RefCounted )
  protected:
    TrackingServer::TrackerType type = TrackingServer::TrackerType::TRACKER_UNKNOWN;
    godot::StringName name = "unknown";
    godot::String description;

    static void _bind_methods();

  public:
    Tracker();
    ~Tracker() override;

    [[nodiscard]] godot::StringName get_tracker_name() const;
    [[nodiscard]] godot::StringName get_tracker_description() const;
    [[nodiscard]] TrackingServer::TrackerType get_tracker_type() const;
};

#endif // VDOT_TRACKER_H
