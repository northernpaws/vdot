

#ifndef VDOT_FACE_TRACKER_PANEL_H
#define VDOT_FACE_TRACKER_PANEL_H

#include <godot_cpp/classes/control.hpp>

class FaceTrackerPanel : public godot::Control {
    GDCLASS( FaceTrackerPanel, godot::Control )
  protected:
    static void _bind_methods();
  public:
    FaceTrackerPanel();
    ~FaceTrackerPanel();
};

#endif // VDOT_FACE_TRACKER_PANEL_H
