

#ifndef VDOT_FACE_TRACKER_PANEL_H
#define VDOT_FACE_TRACKER_PANEL_H

#include <godot_cpp/classes/control.hpp>

#include "../../tracker_face.h"

class FaceTrackerPanel : public godot::Control {
    GDCLASS( FaceTrackerPanel, godot::Control )

    godot::Ref<FaceTracker> _tracker;

  protected:
    static void _bind_methods();

  public:
    FaceTrackerPanel();
    ~FaceTrackerPanel();

    void set_tracker( const godot::Ref<FaceTracker> &p_tracker );
};

#endif // VDOT_FACE_TRACKER_PANEL_H
