

#ifndef VDOT_LIVE_LINK_FACE_TRACKER_H
#define VDOT_LIVE_LINK_FACE_TRACKER_H

#include "../../tracker_face.h"
#include "live_link_server.h"

/**
 * Implements a LiveLink-based face tracker.
 */
class LiveLinkFaceTracker : public FaceTracker {
    GDCLASS( LiveLinkFaceTracker, FaceTracker )

    godot::Ref<LiveLinkClient> _client = nullptr;

  protected:
    static void _bind_methods();

  public:
    LiveLinkFaceTracker() = default;
    explicit LiveLinkFaceTracker( const godot::Ref<LiveLinkClient> &p_client );
    ~LiveLinkFaceTracker() override;

    static godot::StringName tracker_name( const godot::Ref<LiveLinkClient> &client );
};

#endif // VDOT_LIVE_LINK_FACE_TRACKER_H
