
#ifndef VDOT_VTS_FACE_TRACKER_H
#define VDOT_VTS_FACE_TRACKER_H

#include "../../tracker_face.h"

#include "vts_client.h"

/**
 * Implements a VTS-based face tracker.
 */
class VTSFaceTracker : public FaceTracker {
    GDCLASS( VTSFaceTracker, FaceTracker )

    godot::String _address;
    uint32_t _port;

    godot::Ref<VTSClient> _client = nullptr;

  protected:
    static void _bind_methods();

  public:
    VTSFaceTracker() = default;
    explicit VTSFaceTracker( const godot::String& p_address, uint32_t p_port );
    ~VTSFaceTracker() override;
};

#endif // VDOT_VTS_FACE_TRACKER_H
