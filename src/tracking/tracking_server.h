
#ifndef VDOT_TRACKING_SERVER_H
#define VDOT_TRACKING_SERVER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/templates/vector.hpp>

class TrackingInterface;
class Tracker;

/**
 * Provides the Godot server for face and body tracking.
 *
 * In the future this will be replaced with Godot's XRServer, but for
 * now while that is experimental, we'll use our own implementation.
 */
class TrackingServer : public godot::Object {
    GDCLASS( TrackingServer, godot::Object )

    godot::Vector<godot::Ref<TrackingInterface>> _interfaces;

    godot::Dictionary _trackers;

  public:
    // NOTE: mirroring values from Godot's experimental XR interface for eventual compatability.
    //  ref:
    //  https://github.com/godotengine/godot/blob/eb5103093c1bfd4d527ec1255d28e9bc8d3625b5/servers/xr_server.h#L68
    enum TrackerType {
        TRACKER_FACE = 0x40,
        TRACKER_UNKNOWN = 0x80,
    };

  protected:
    static TrackingServer *singleton;

    static void _bind_methods();

  public:
    static TrackingServer *get_singleton();

    TrackingServer();
    ~TrackingServer() override;

    void _notification(int p_what);

    void _process();

    void add_interface( const godot::Ref<TrackingInterface> &p_interface );
    void remove_interface( const godot::Ref<TrackingInterface> &p_interface );
    int get_interface_count() const;
    godot::Ref<TrackingInterface> get_interface( int p_index ) const;
    godot::Ref<TrackingInterface> find_interface( const godot::String &p_name ) const;
    godot::TypedArray<godot::Dictionary> get_interfaces() const;

    void add_tracker( const godot::Ref<Tracker> &p_tracker );
    void remove_tracker( const godot::Ref<Tracker> &p_tracker );
    godot::Dictionary get_trackers( TrackerType p_tracker_types );
    godot::Ref<Tracker> get_tracker( const godot::StringName &p_name ) const;


};

VARIANT_ENUM_CAST( TrackingServer::TrackerType );

#endif // VDOT_TRACKING_SERVER_H
