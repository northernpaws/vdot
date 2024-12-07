

#include "face_tracker_panel.h"

void FaceTrackerPanel::_bind_methods() {
}

FaceTrackerPanel::FaceTrackerPanel() {
}

FaceTrackerPanel::~FaceTrackerPanel() {
}

void FaceTrackerPanel::set_tracker( const godot::Ref<FaceTracker> &p_tracker ) {
    _tracker = p_tracker;
}