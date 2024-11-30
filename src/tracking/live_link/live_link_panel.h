

#ifndef VDOT_LIVE_LINK_PANEL_H
#define VDOT_LIVE_LINK_PANEL_H

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/variant/variant.hpp"

#include "live_link_server.h"

class LiveLinkPanel : public godot::Control {
    GDCLASS(LiveLinkPanel, godot::Object)

    godot::MeshInstance3D* _mesh;

    LiveLinkServer* _server;

    bool _server_active = false;
protected:
    static void _bind_methods();
public:
    LiveLinkPanel();
    ~LiveLinkPanel() override;

    void _process(double delta) override;

    void update_mesh(const LiveLinkClientData* data);

    void _on_server_client_connected (LiveLinkClient* client);
    void _on_server_client_disconnected (LiveLinkClient* client);
    void _on_server_client_updated (LiveLinkClient* client);
};

#endif // VDOT_LIVE_LINK_PANEL_H
