
#include "tracker_face.h"

void FaceTracker::_bind_methods() {
    // Base Shapes
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_OUT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_IN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_UP_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_DOWN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_OUT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_IN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_UP_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_LOOK_DOWN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CLOSED_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CLOSED_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_SQUINT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_SQUINT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_WIDE_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_WIDE_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_DILATION_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_DILATION_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CONSTRICT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CONSTRICT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_PINCH_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_PINCH_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_LOWERER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_LOWERER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_INNER_UP_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_INNER_UP_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_OUTER_UP_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_OUTER_UP_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NOSE_SNEER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NOSE_SNEER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_DILATION_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_DILATION_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_CONSTRICT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_CONSTRICT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SQUINT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SQUINT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_PUFF_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_PUFF_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SUCK_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SUCK_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_OPEN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_CLOSED );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_FORWARD );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_BACKWARD );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_CLENCH );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_JAW_MANDIBLE_RAISE );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_UPPER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_UPPER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_LOWER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_LOWER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_CORNER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_CORNER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_UPPER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_UPPER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_LOWER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_LOWER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_UPPER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_UPPER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_LOWER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_LOWER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_UP_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_UP_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_DOWN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_DOWN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_DEEPEN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_DEEPEN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_PULL_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_PULL_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_SLANT_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_SLANT_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_FROWN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_FROWN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_STRETCH_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_STRETCH_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_DIMPLE_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_DIMPLE_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_RAISER_UPPER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_RAISER_LOWER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_PRESS_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_PRESS_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_TIGHTENER_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_TIGHTENER_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_OUT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_UP );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_DOWN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_ROLL );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_BLEND_DOWN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_CURL_UP );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_SQUISH );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_FLAT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_TWIST_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_TONGUE_TWIST_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_SOFT_PALATE_CLOSE );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_THROAT_SWALLOW );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NECK_FLEX_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NECK_FLEX_LEFT );
    // Blended Shapes
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CLOSED );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_WIDE );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_SQUINT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_DILATION );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_EYE_CONSTRICT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_DOWN_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_DOWN_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_DOWN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_UP_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_UP_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_BROW_UP );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NOSE_SNEER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_DILATION );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_NASAL_CONSTRICT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_PUFF );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SUCK );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_CHEEK_SQUINT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_UPPER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK_LOWER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_SUCK );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_UPPER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_LOWER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_UPPER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_LOWER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_LIP_PUCKER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_UP );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_DOWN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_OPEN );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SMILE_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SMILE_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SMILE );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SAD_RIGHT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SAD_LEFT );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_SAD );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_STRETCH );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_DIMPLE );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_TIGHTENER );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MOUTH_PRESS );
    BIND_ENUM_CONSTANT( UnifiedExpressions::BlendShape::FT_MAX );

    ADD_SIGNAL( godot::MethodInfo(
        "blend_shape_updated", godot::PropertyInfo( godot::Variant::INT, "blend_shape"),
        godot::PropertyInfo( godot::Variant::FLOAT, "weight")) );

    ADD_SIGNAL( godot::MethodInfo( "blend_shapes_updated" ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_blend_shape", "blend_shape" ),
                                 &FaceTracker::get_blend_shape );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_blend_shape", "blend_shape", "weight" ),
                                 &FaceTracker::set_blend_shape );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_blend_shape_name", "blend_shape" ),
                                 &FaceTracker::get_blend_shape_name );

    godot::ClassDB::bind_method(godot::D_METHOD("get_blend_shapes"), &FaceTracker::get_blend_shapes);
    godot::ClassDB::bind_method(godot::D_METHOD("set_blend_shapes", "weights"), &FaceTracker::set_blend_shapes);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::PACKED_FLOAT32_ARRAY, "blend_shapes"), "set_blend_shapes", "get_blend_shapes");
}

FaceTracker::FaceTracker() {
    type = TrackingServer::TRACKER_FACE;
}
FaceTracker::~FaceTracker() = default;

float FaceTracker::get_blend_shape( UnifiedExpressions::BlendShape blend_shape ) const {
    // Fail if the blend shape index is out of range.
    ERR_FAIL_INDEX_V( blend_shape, UnifiedExpressions::BlendShape::FT_MAX, 0.0f );

    return blend_shape_values[blend_shape];
}

void FaceTracker::set_blend_shape( UnifiedExpressions::BlendShape blend_shape, float weight ) {
    // Fail if the blend shape index is out of range.
    ERR_FAIL_INDEX( blend_shape, UnifiedExpressions::BlendShape::FT_MAX );

    blend_shape_values[blend_shape] = weight;

    emit_signal("blend_shape_updated", blend_shape, weight);
}

godot::PackedFloat32Array FaceTracker::get_blend_shapes() const {
    // Create a packed float32 array and copy the blend shape values into it.
    godot::PackedFloat32Array data;
    data.resize(UnifiedExpressions::BlendShape::FT_MAX);
    memcpy(data.ptrw(), blend_shape_values, sizeof(blend_shape_values));

    // Return the blend shape array.
    return data;
}

void FaceTracker::set_blend_shapes(const godot::PackedFloat32Array &p_blend_shapes) {
    // Fail if the blend shape array is not the correct size.
    ERR_FAIL_COND(p_blend_shapes.size() != UnifiedExpressions::BlendShape::FT_MAX);

    // Copy the blend shape values into the blend shape array.
    memcpy(blend_shape_values, p_blend_shapes.ptr(), sizeof(blend_shape_values));

    emit_signal("blend_shapes_updated");
}

godot::StringName FaceTracker::get_blend_shape_name(UnifiedExpressions::BlendShape blend_shape) {
    return UnifiedExpressions::blend_shape_names[blend_shape];
}