

#ifndef VDOT_VTS_INTERFACE_H
#define VDOT_VTS_INTERFACE_H

#include "../../tracking_interface.h"

#include "../../standards/unified_expressions.h"

#include "vts_face_tracker.h"

/**
 * Implements a face/body tracking interface using VTS to
 *  receive and process facial tracking data from a phone.
 *
 * This works a little differently from the LiveLink interface,
 *  in that a connection needs to initialized from the VTS interface
 *  TO the device sending, instead of the sending device connecting
 *  to a local server.
 */
class VTSInterface : public TrackingInterface {
    GDCLASS( VTSInterface, TrackingInterface )

    bool _initialized = false;

    godot::Dictionary _trackers;

  protected:
    static VTSInterface *singleton;

    static void _bind_methods();

  public:
    static VTSInterface *get_singleton();

    VTSInterface();
    ~VTSInterface() override;

    [[nodiscard]] godot::StringName get_name() const override {
        return "VTS";
    };

    bool is_initialized() override;
    bool initialize() override;
    void uninitialize() override;

    void process() override;

    /**
     * Called by the game to register a new tracker endpoint with the VTS interface.
     *
     * This will create a new VTS facial tracker for the specified address and port.
     *
     * @param address - IP or DNS address of the device running the VTS server.
     * @param port - Port of the VTS server on the device.
     * @return The created tracker.
     */
    godot::Ref<VTSFaceTracker> register_tracker( const godot::String &address, uint16_t port );
};

#endif // VDOT_VTS_INTERFACE_H
