

#ifndef VDOT_LIVE_LINK_INTERFACE_H
#define VDOT_LIVE_LINK_INTERFACE_H

#include "../../tracking_interface.h"

#include "../../standards/unified_expressions.h"

#include "live_link_server.h"

/**
 * Implements a face/body tracking interface using LiveLink to
 *  receive and process facial tracking data from an iPhone.
 */
class LiveLinkInterface : public TrackingInterface {
    GDCLASS( LiveLinkInterface, TrackingInterface )

    bool _initialized = false;

    godot::Ref<LiveLinkServer> _server;

    godot::Dictionary _trackers;

  protected:
    static void _bind_methods();

  public:
    LiveLinkInterface();
    ~LiveLinkInterface() override;

    [[nodiscard]] godot::StringName get_name() const override {
        return "LiveLink";
    };

    bool is_initialized() override;
    bool initialize() override;
    void uninitialize() override;

    void process() override;

    void _on_server_client_connected( const godot::Ref<LiveLinkClient> &client );
    void _on_server_client_disconnected( const godot::Ref<LiveLinkClient> &client );
    void _on_server_client_updated( const godot::Ref<LiveLinkClient> &client );
};

#endif // VDOT_LIVE_LINK_INTERFACE_H
