// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2014-present Godot Engine contributors

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_TRACKER_FACE_H
#define VDOT_TRACKER_FACE_H

#include "standards/unified_expressions.h"

#include "tracker.h"

/**
 * Implements a tracker for facial expression tracking.
 */
class FaceTracker : public Tracker {
    GDCLASS( FaceTracker, Tracker )
  public:
  protected:
    static void _bind_methods();

    float blend_shape_values[UnifiedExpressions::BlendShape::FT_MAX] = {};

  public:
    FaceTracker();
    ~FaceTracker() override;

    [[nodiscard]] float get_blend_shape( UnifiedExpressions::BlendShape blend_shape ) const;
    void set_blend_shape( UnifiedExpressions::BlendShape blend_shape, float weight );

    [[nodiscard]] godot::PackedFloat32Array get_blend_shapes() const;
    void set_blend_shapes( const godot::PackedFloat32Array &p_blend_shapes );

    godot::StringName get_blend_shape_name( UnifiedExpressions::BlendShape blend_shape );

    [[nodiscard]] UnifiedExpressions::BlendShape get_arkit_blend_shape(
        ARKit::BlendShape blend_shape ) const;
    [[nodiscard]] float get_arkit_blend_shape_weight( ARKit::BlendShape blend_shape ) const;
};

VARIANT_ENUM_CAST( UnifiedExpressions::BlendShape );

#endif // VDOT_TRACKER_FACE_H
