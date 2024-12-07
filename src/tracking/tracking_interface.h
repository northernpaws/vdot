
#ifndef VDOT_TRACKING_INTERFACE_H
#define VDOT_TRACKING_INTERFACE_H

#include <godot_cpp/classes/ref_counted.hpp>

class TrackingInterface : public godot::RefCounted {
    GDCLASS( TrackingInterface, godot::RefCounted )
  protected:
    static void _bind_methods();

  public:
    TrackingInterface();
    ~TrackingInterface() override;

    virtual godot::StringName get_name() const {
        return "Unknown";
    };

    virtual bool is_initialized() {
        return false;
    };
    virtual bool initialize() {
        return false;
    };
    virtual void uninitialize() {};

    virtual void process() {};
};

#endif // VDOT_TRACKING_INTERFACE_H
