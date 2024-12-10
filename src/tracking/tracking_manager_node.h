
#ifndef VDOT_TRACKING_MANAGER_NODE_H
#define VDOT_TRACKING_MANAGER_NODE_H

#include <godot_cpp/classes/node.hpp>

/**
 * Hack node to send _process calls to the tracking server.
 *
 * TODO: replace with better solution
 */
class TrackingManagerNode : public godot::Node {
    GDCLASS( TrackingManagerNode, godot::Node )
  protected:
    static void _bind_methods();

  public:
    void _enter_tree() override;

    void _process( double p_delta ) override;

    [[nodiscard]] godot::PackedStringArray _get_configuration_warnings() const override;
};

#endif // VDOT_TRACKING_MANAGER_NODE_H
