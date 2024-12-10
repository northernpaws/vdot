

#ifndef VDOT_CUBISM_EFFECT_FACE_TRACKING_H
#define VDOT_CUBISM_EFFECT_FACE_TRACKING_H


#include <CubismDefaultParameterId.hpp>
#include <CubismFramework.hpp>
#include <Id/CubismIdManager.hpp>

#include "models/2d/live2d/cubism.h"

#include "models/2d/live2d/cubism_effect.h"
#include "models/2d/live2d/renderer/cubism_model_proxy.h"

#include "tracking/tracker_face.h"

class CubismEffectFaceTracking : public CubismEffect {
    GDCLASS( CubismEffectFaceTracking, CubismEffect )

    godot::Ref<FaceTracker> _tracker = nullptr;

  protected:
    static void _bind_methods();
  public:
    CubismEffectFaceTracking();

    void _enter_tree() override;
    void _exit_tree() override;

    void _cubism_init( CubismModelProxy *model ) override;

    void _cubism_term( CubismModelProxy *model ) override;

    void _cubism_process( CubismModelProxy *model, const float delta ) override;

    bool _set(const godot::StringName &p_name, const godot::Variant &p_property);
    bool _get(const godot::StringName &p_name, godot::Variant &r_property) const;
    void _get_property_list(godot::List<godot::PropertyInfo> *p_list) const;

    void _server_tracker_added(const godot::StringName& p_tracker_name, TrackingServer::TrackerType p_tracker_type);
};


#endif // VDOT_CUBISM_EFFECT_FACE_TRACKING_H
