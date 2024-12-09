
#include "unified_expressions.h"

namespace UnifiedExpressions {
    godot::HashMap<BlendShape, godot::String> blend_shape_names;

    godot::HashMap<BlendShape, ARKit::BlendShape> unified_to_arkit;
    godot::HashMap<ARKit::BlendShape, BlendShape> arkit_to_unified;

    void _init_blend_shape_names() {
        blend_shape_names.clear();

        blend_shape_names[FT_EYE_LOOK_OUT_RIGHT] = "Right eye looks outwards";
        blend_shape_names[FT_EYE_LOOK_IN_RIGHT] = "Right eye looks inwards";
        blend_shape_names[FT_EYE_LOOK_UP_RIGHT] = "Right eye looks upwards";
        blend_shape_names[FT_EYE_LOOK_DOWN_RIGHT] = "Right eye looks downwards";
        blend_shape_names[FT_EYE_LOOK_OUT_LEFT] = "Left eye looks outwards";
        blend_shape_names[FT_EYE_LOOK_IN_LEFT] = "Left eye looks inwards";
        blend_shape_names[FT_EYE_LOOK_UP_LEFT] = "Left eye looks upwards";
        blend_shape_names[FT_EYE_LOOK_DOWN_LEFT] = "Left eye looks downwards";
        blend_shape_names[FT_EYE_CLOSED_RIGHT] = "Closes the right eyelid";
        blend_shape_names[FT_EYE_CLOSED_LEFT] = "Closes the left eyelid";
        blend_shape_names[FT_EYE_SQUINT_RIGHT] = "Squeezes the right eye socket muscles";
        blend_shape_names[FT_EYE_SQUINT_LEFT] = "Squeezes the left eye socket muscles";
        blend_shape_names[FT_EYE_WIDE_RIGHT] = "Right eyelid widens beyond relaxed";
        blend_shape_names[FT_EYE_WIDE_LEFT] = "Left eyelid widens beyond relaxed";
        blend_shape_names[FT_EYE_DILATION_RIGHT] = "Dilates the right eye pupil";
        blend_shape_names[FT_EYE_DILATION_LEFT] = "Dilates the left eye pupil";
        blend_shape_names[FT_EYE_CONSTRICT_RIGHT] = "Constricts the right eye pupil";
        blend_shape_names[FT_EYE_CONSTRICT_LEFT] = "Constricts the left eye pupil";
        blend_shape_names[FT_BROW_PINCH_RIGHT] = "Right eyebrow pinches in";
        blend_shape_names[FT_BROW_PINCH_LEFT] = "Left eyebrow pinches in";
        blend_shape_names[FT_BROW_LOWERER_RIGHT] = "Outer right eyebrow pulls down";
        blend_shape_names[FT_BROW_LOWERER_LEFT] = "Outer left eyebrow pulls down";
        blend_shape_names[FT_BROW_INNER_UP_RIGHT] = "Inner right eyebrow pulls up";
        blend_shape_names[FT_BROW_INNER_UP_LEFT] = "Inner left eyebrow pulls up";
        blend_shape_names[FT_BROW_OUTER_UP_RIGHT] = "Outer right eyebrow pulls up";
        blend_shape_names[FT_BROW_OUTER_UP_LEFT] = "Outer left eyebrow pulls up";
        blend_shape_names[FT_NOSE_SNEER_RIGHT] = "Right side face sneers";
        blend_shape_names[FT_NOSE_SNEER_LEFT] = "Left side face sneers";
        blend_shape_names[FT_NASAL_DILATION_RIGHT] = "Right side nose canal dilates";
        blend_shape_names[FT_NASAL_DILATION_LEFT] = "Left side nose canal dilates";
        blend_shape_names[FT_NASAL_CONSTRICT_RIGHT] = "Right side nose canal constricts";
        blend_shape_names[FT_NASAL_CONSTRICT_LEFT] = "Left side nose canal constricts";
        blend_shape_names[FT_CHEEK_SQUINT_RIGHT] = "Raises the right side cheek";
        blend_shape_names[FT_CHEEK_SQUINT_LEFT] = "Raises the left side cheek";
        blend_shape_names[FT_CHEEK_PUFF_RIGHT] = "Puffs the right side cheek";
        blend_shape_names[FT_CHEEK_PUFF_LEFT] = "Puffs the left side cheek";
        blend_shape_names[FT_CHEEK_SUCK_RIGHT] = "Sucks in the right side cheek";
        blend_shape_names[FT_CHEEK_SUCK_LEFT] = "Sucks in the left side cheek";
        blend_shape_names[FT_JAW_OPEN] = "Opens jawbone";
        blend_shape_names[FT_MOUTH_CLOSED] = "Closes the mouth";
        blend_shape_names[FT_JAW_RIGHT] = "Pushes jawbone right";
        blend_shape_names[FT_JAW_LEFT] = "Pushes jawbone left";
        blend_shape_names[FT_JAW_FORWARD] = "Pushes jawbone forward";
        blend_shape_names[FT_JAW_BACKWARD] = "Pushes jawbone backward";
        blend_shape_names[FT_JAW_CLENCH] = "Flexes jaw muscles";
        blend_shape_names[FT_JAW_MANDIBLE_RAISE] = "Raises the jawbone";
        blend_shape_names[FT_LIP_SUCK_UPPER_RIGHT] = "Upper right lip part tucks in the mouth";
        blend_shape_names[FT_LIP_SUCK_UPPER_LEFT] = "Upper left lip part tucks in the mouth";
        blend_shape_names[FT_LIP_SUCK_LOWER_RIGHT] = "Lower right lip part tucks in the mouth";
        blend_shape_names[FT_LIP_SUCK_LOWER_LEFT] = "Lower left lip part tucks in the mouth";
        blend_shape_names[FT_LIP_SUCK_CORNER_RIGHT] = "Right lip corner folds into the mouth";
        blend_shape_names[FT_LIP_SUCK_CORNER_LEFT] = "Left lip corner folds into the mouth";
        blend_shape_names[FT_LIP_FUNNEL_UPPER_RIGHT] = "Upper right lip part pushes into a funnel";
        blend_shape_names[FT_LIP_FUNNEL_UPPER_LEFT] = "Upper left lip part pushes into a funnel";
        blend_shape_names[FT_LIP_FUNNEL_LOWER_RIGHT] = "Lower right lip part pushes into a funnel";
        blend_shape_names[FT_LIP_FUNNEL_LOWER_LEFT] = "Lower left lip part pushes into a funnel";
        blend_shape_names[FT_LIP_PUCKER_UPPER_RIGHT] = "Upper right lip part pushes outwards";
        blend_shape_names[FT_LIP_PUCKER_UPPER_LEFT] = "Upper left lip part pushes outwards";
        blend_shape_names[FT_LIP_PUCKER_LOWER_RIGHT] = "Lower right lip part pushes outwards";
        blend_shape_names[FT_LIP_PUCKER_LOWER_LEFT] = "Lower left lip part pushes outwards";
        blend_shape_names[FT_MOUTH_UPPER_UP_RIGHT] = "Upper right part of the lip pulls up";
        blend_shape_names[FT_MOUTH_UPPER_UP_LEFT] = "Upper left part of the lip pulls up";
        blend_shape_names[FT_MOUTH_LOWER_DOWN_RIGHT] = "Lower right part of the lip pulls up";
        blend_shape_names[FT_MOUTH_LOWER_DOWN_LEFT] = "Lower left part of the lip pulls up";
        blend_shape_names[FT_MOUTH_UPPER_DEEPEN_RIGHT] = "Upper right lip part pushes in the cheek";
        blend_shape_names[FT_MOUTH_UPPER_DEEPEN_LEFT] = "Upper left lip part pushes in the cheek";
        blend_shape_names[FT_MOUTH_UPPER_RIGHT] = "Moves upper lip right";
        blend_shape_names[FT_MOUTH_UPPER_LEFT] = "Moves upper lip left";
        blend_shape_names[FT_MOUTH_LOWER_RIGHT] = "Moves lower lip right";
        blend_shape_names[FT_MOUTH_LOWER_LEFT] = "Moves lower lip left";
        blend_shape_names[FT_MOUTH_CORNER_PULL_RIGHT] = "Right lip corner pulls diagonally up and out";
        blend_shape_names[FT_MOUTH_CORNER_PULL_LEFT] = "Left lip corner pulls diagonally up and out";
        blend_shape_names[FT_MOUTH_CORNER_SLANT_RIGHT] = "Right corner lip slants up";
        blend_shape_names[FT_MOUTH_CORNER_SLANT_LEFT] = "Left corner lip slants up";
        blend_shape_names[FT_MOUTH_FROWN_RIGHT] = "Right corner lip pulls down";
        blend_shape_names[FT_MOUTH_FROWN_LEFT] = "Left corner lip pulls down";
        blend_shape_names[FT_MOUTH_STRETCH_RIGHT] = "Mouth corner lip pulls out and down";
        blend_shape_names[FT_MOUTH_STRETCH_LEFT] = "Mouth corner lip pulls out and down";
        blend_shape_names[FT_MOUTH_DIMPLE_RIGHT] = "Right lip corner is pushed backwards";
        blend_shape_names[FT_MOUTH_DIMPLE_LEFT] = "Left lip corner is pushed backwards";
        blend_shape_names[FT_MOUTH_RAISER_UPPER] = "Raises and slightly pushes out the upper mouth";
        blend_shape_names[FT_MOUTH_RAISER_LOWER] = "Raises and slightly pushes out the lower mouth";
        blend_shape_names[FT_MOUTH_PRESS_RIGHT] = "Right side lips press and flatten together vertically";
        blend_shape_names[FT_MOUTH_PRESS_LEFT] = "Left side lips press and flatten together vertically";
        blend_shape_names[FT_MOUTH_TIGHTENER_RIGHT] = "Right side lips squeeze together horizontally";
        blend_shape_names[FT_MOUTH_TIGHTENER_LEFT] = "Left side lips squeeze together horizontally";
        blend_shape_names[FT_TONGUE_OUT] = "Tongue visibly sticks out of the mouth";
        blend_shape_names[FT_TONGUE_UP] = "Tongue points upwards";
        blend_shape_names[FT_TONGUE_DOWN] = "Tongue points downwards";
        blend_shape_names[FT_TONGUE_RIGHT] = "Tongue points right";
        blend_shape_names[FT_TONGUE_LEFT] = "Tongue points left";
        blend_shape_names[FT_TONGUE_ROLL] = "Sides of the tongue funnel, creating a roll";
        blend_shape_names[FT_TONGUE_BLEND_DOWN] = "Tongue arches up then down inside the mouth";
        blend_shape_names[FT_TONGUE_CURL_UP] = "Tongue arches down then up inside the mouth";
        blend_shape_names[FT_TONGUE_SQUISH] = "Tongue squishes together and thickens";
        blend_shape_names[FT_TONGUE_FLAT] = "Tongue flattens and thins out";
        blend_shape_names[FT_TONGUE_TWIST_RIGHT] = "Tongue tip rotates clockwise, with the rest following gradually";
        blend_shape_names[FT_TONGUE_TWIST_LEFT] = "Tongue tip rotates counter-clockwise, with the rest followin";
                                             // gradually.
        blend_shape_names[FT_SOFT_PALATE_CLOSE] = "Inner mouth throat closes";
        blend_shape_names[FT_THROAT_SWALLOW] = "The Adam's apple visibly swallows";
        blend_shape_names[FT_NECK_FLEX_RIGHT] = "Right side neck visibly flexes";
        blend_shape_names[FT_NECK_FLEX_LEFT] = "Left side neck visibly flexes";
                // Blended Shapes
        blend_shape_names[FT_EYE_CLOSED] = "Closes both eye lids";
        blend_shape_names[FT_EYE_WIDE] = "Widens both eye lids";
        blend_shape_names[FT_EYE_SQUINT] = "Squints both eye lids";
        blend_shape_names[FT_EYE_DILATION] = "Dilates both pupils";
        blend_shape_names[FT_EYE_CONSTRICT] = "Constricts both pupils";
        blend_shape_names[FT_BROW_DOWN_RIGHT] = "Pulls the right eyebrow down and in";
        blend_shape_names[FT_BROW_DOWN_LEFT] = "Pulls the left eyebrow down and in";
        blend_shape_names[FT_BROW_DOWN] = "Pulls both eyebrows down and in";
        blend_shape_names[FT_BROW_UP_RIGHT] = "Right brow appears worried";
        blend_shape_names[FT_BROW_UP_LEFT] = "Left brow appears worried";
        blend_shape_names[FT_BROW_UP] = "Both brows appear worried";
        blend_shape_names[FT_NOSE_SNEER] = "Entire face sneers";
        blend_shape_names[FT_NASAL_DILATION] = "Both nose canals dilate";
        blend_shape_names[FT_NASAL_CONSTRICT] = "Both nose canals constrict";
        blend_shape_names[FT_CHEEK_PUFF] = "Puffs both cheeks";
        blend_shape_names[FT_CHEEK_SUCK] = "Sucks in both cheeks";
        blend_shape_names[FT_CHEEK_SQUINT] = "Raises both cheeks";
        blend_shape_names[FT_LIP_SUCK_UPPER] = "Tucks in the upper lips";
        blend_shape_names[FT_LIP_SUCK_LOWER] = "Tucks in the lower lips";
        blend_shape_names[FT_LIP_SUCK] = "Tucks in both lips";
        blend_shape_names[FT_LIP_FUNNEL_UPPER] = "Funnels in the upper lips";
        blend_shape_names[FT_LIP_FUNNEL_LOWER] = "Funnels in the lower lips";
        blend_shape_names[FT_LIP_FUNNEL] = "Funnels in both lips";
        blend_shape_names[FT_LIP_PUCKER_UPPER] = "Upper lip part pushes outwards";
        blend_shape_names[FT_LIP_PUCKER_LOWER] = "Lower lip part pushes outwards";
        blend_shape_names[FT_LIP_PUCKER] = "Lips push outwards";
        blend_shape_names[FT_MOUTH_UPPER_UP] = "Raises the upper lips";
        blend_shape_names[FT_MOUTH_LOWER_DOWN] = "Lowers the lower lips";
        blend_shape_names[FT_MOUTH_OPEN] = "Mouth opens, revealing teeth";
        blend_shape_names[FT_MOUTH_RIGHT] = "Moves mouth right";
        blend_shape_names[FT_MOUTH_LEFT] = "Moves mouth left";
        blend_shape_names[FT_MOUTH_SMILE_RIGHT] = "Right side of the mouth smiles";
        blend_shape_names[FT_MOUTH_SMILE_LEFT] = "Left side of the mouth smiles";
        blend_shape_names[FT_MOUTH_SMILE] = "Mouth expresses a smile";
        blend_shape_names[FT_MOUTH_SAD_RIGHT] = "Right side of the mouth expresses sadness";
        blend_shape_names[FT_MOUTH_SAD_LEFT] = "Left side of the mouth expresses sadness";
        blend_shape_names[FT_MOUTH_SAD] = "Mouth expresses sadness";
        blend_shape_names[FT_MOUTH_STRETCH] = "Mouth stretches";
        blend_shape_names[FT_MOUTH_DIMPLE] = "Lip corners dimple";
        blend_shape_names[FT_MOUTH_TIGHTENER] = "Mouth tightens";
        blend_shape_names[FT_MOUTH_PRESS] = "Mouth presses together";
    }

    void _init_arkit_unified_mappings() {
        unified_to_arkit.clear();

        unified_to_arkit[FT_EYE_LOOK_OUT_RIGHT] = ARKit::BlendShape::EyeLookOutRight;
        unified_to_arkit[FT_EYE_LOOK_IN_RIGHT] = ARKit::BlendShape::EyeLookInRight;
        unified_to_arkit[FT_EYE_LOOK_UP_RIGHT] = ARKit::BlendShape::EyeLookUpRight;
        unified_to_arkit[FT_EYE_LOOK_DOWN_RIGHT] = ARKit::BlendShape::EyeLookDownRight;
        unified_to_arkit[FT_EYE_LOOK_OUT_LEFT] = ARKit::BlendShape::EyeLookOutLeft;
        unified_to_arkit[FT_EYE_LOOK_IN_LEFT] = ARKit::BlendShape::EyeLookInLeft;
        unified_to_arkit[FT_EYE_LOOK_UP_LEFT] = ARKit::BlendShape::EyeLookUpLeft;
        unified_to_arkit[FT_EYE_LOOK_DOWN_LEFT] = ARKit::BlendShape::EyeLookDownLeft;
        unified_to_arkit[FT_EYE_CLOSED_RIGHT] = ARKit::BlendShape::EyeBlinkRight;
        unified_to_arkit[FT_EYE_CLOSED_LEFT] = ARKit::BlendShape::EyeBlinkLeft;
        unified_to_arkit[FT_EYE_SQUINT_RIGHT] = ARKit::BlendShape::EyeSquintRight;
        unified_to_arkit[FT_EYE_SQUINT_LEFT] = ARKit::BlendShape::EyeSquintLeft;
        unified_to_arkit[FT_EYE_WIDE_RIGHT] = ARKit::BlendShape::EyeWideRight;
        unified_to_arkit[FT_EYE_WIDE_LEFT] = ARKit::BlendShape::EyeWideLeft;
        unified_to_arkit[FT_BROW_PINCH_RIGHT] = ARKit::BlendShape::BrowDownRight;
        unified_to_arkit[FT_BROW_PINCH_LEFT] = ARKit::BlendShape::BrowDownLeft;
        unified_to_arkit[FT_BROW_INNER_UP_RIGHT] = ARKit::BlendShape::BrowInnerUp;
        unified_to_arkit[FT_BROW_OUTER_UP_RIGHT] = ARKit::BlendShape::BrowOuterUpRight;
        unified_to_arkit[FT_BROW_OUTER_UP_LEFT] = ARKit::BlendShape::BrowOuterUpLeft;
        unified_to_arkit[FT_NOSE_SNEER_RIGHT] = ARKit::BlendShape::NoseSneerRight;
        unified_to_arkit[FT_NOSE_SNEER_LEFT] = ARKit::BlendShape::NoseSneerLeft;
        unified_to_arkit[FT_CHEEK_SQUINT_RIGHT] = ARKit::BlendShape::CheekSquintRight;
        unified_to_arkit[FT_CHEEK_SQUINT_LEFT] = ARKit::BlendShape::CheekSquintLeft;
        unified_to_arkit[FT_CHEEK_PUFF_RIGHT] = ARKit::BlendShape::CheekPuff;
        unified_to_arkit[FT_JAW_OPEN] = ARKit::BlendShape::JawOpen;
        unified_to_arkit[FT_MOUTH_CLOSED] = ARKit::BlendShape::MouthClose;
        unified_to_arkit[FT_JAW_RIGHT] = ARKit::BlendShape::JawRight;
        unified_to_arkit[FT_JAW_LEFT] = ARKit::BlendShape::JawLeft;
        unified_to_arkit[FT_JAW_FORWARD] = ARKit::BlendShape::JawForward;
        unified_to_arkit[FT_LIP_SUCK_UPPER_RIGHT] = ARKit::BlendShape::MouthRollUpper;
        unified_to_arkit[FT_LIP_SUCK_LOWER_RIGHT] = ARKit::BlendShape::MouthRollLower;
        unified_to_arkit[FT_LIP_FUNNEL_UPPER_RIGHT] = ARKit::BlendShape::MouthFunnel;
        unified_to_arkit[FT_LIP_PUCKER_UPPER_RIGHT] = ARKit::BlendShape::MouthPucker;
        unified_to_arkit[FT_MOUTH_UPPER_UP_RIGHT] = ARKit::BlendShape::MouthPucker;  // 2 NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_UPPER_UP_LEFT] = ARKit::BlendShape::MouthUpperUpLeft; // 2 NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_LOWER_DOWN_RIGHT] = ARKit::BlendShape::MouthLowerDownRight;
        unified_to_arkit[FT_MOUTH_LOWER_DOWN_LEFT] = ARKit::BlendShape::MouthLowerDownLeft;
        unified_to_arkit[FT_MOUTH_UPPER_RIGHT] = ARKit::BlendShape::MouthRight; // NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_UPPER_LEFT] = ARKit::BlendShape::MouthLeft; // NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_CORNER_PULL_RIGHT] = ARKit::BlendShape::MouthSmileRight; // NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_CORNER_PULL_LEFT] = ARKit::BlendShape::MouthSmileLeft; // NOTE = not in official mapping
        unified_to_arkit[FT_MOUTH_FROWN_RIGHT] = ARKit::BlendShape::MouthFrownRight;
        unified_to_arkit[FT_MOUTH_FROWN_LEFT] = ARKit::BlendShape::MouthFrownLeft;
        unified_to_arkit[FT_MOUTH_STRETCH_RIGHT] = ARKit::BlendShape::MouthStretchRight;
        unified_to_arkit[FT_MOUTH_STRETCH_LEFT] = ARKit::BlendShape::MouthStretchLeft;
        unified_to_arkit[FT_MOUTH_DIMPLE_RIGHT] = ARKit::BlendShape::MouthDimpleRight;
        unified_to_arkit[FT_MOUTH_DIMPLE_LEFT] = ARKit::BlendShape::MouthDimpleLeft;
        unified_to_arkit[FT_MOUTH_RAISER_UPPER] = ARKit::BlendShape::MouthShrugUpper;
        unified_to_arkit[FT_MOUTH_RAISER_LOWER] = ARKit::BlendShape::MouthShrugLower;
        unified_to_arkit[FT_MOUTH_PRESS_RIGHT] = ARKit::BlendShape::MouthPressRight;
        unified_to_arkit[FT_MOUTH_PRESS_LEFT] = ARKit::BlendShape::MouthPressLeft;
        unified_to_arkit[FT_TONGUE_OUT] = ARKit::BlendShape::TongueOut;

        arkit_to_unified.clear();

        arkit_to_unified[ARKit::BlendShape::EyeLookOutRight] = FT_EYE_LOOK_OUT_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeLookInRight] = FT_EYE_LOOK_IN_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeLookUpRight] = FT_EYE_LOOK_UP_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeLookDownRight] = FT_EYE_LOOK_DOWN_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeLookOutLeft] = FT_EYE_LOOK_OUT_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeLookInLeft] = FT_EYE_LOOK_IN_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeLookUpLeft] = FT_EYE_LOOK_UP_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeLookDownLeft] = FT_EYE_LOOK_DOWN_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeBlinkRight] = FT_EYE_CLOSED_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeBlinkLeft] = FT_EYE_CLOSED_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeSquintRight] = FT_EYE_SQUINT_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeSquintLeft] = FT_EYE_SQUINT_LEFT;
        arkit_to_unified[ARKit::BlendShape::EyeWideRight] = FT_EYE_WIDE_RIGHT;
        arkit_to_unified[ARKit::BlendShape::EyeWideLeft] = FT_EYE_WIDE_LEFT;
        arkit_to_unified[ARKit::BlendShape::BrowDownRight] = FT_BROW_PINCH_RIGHT;
        arkit_to_unified[ARKit::BlendShape::BrowDownLeft] = FT_BROW_PINCH_LEFT;
        arkit_to_unified[ARKit::BlendShape::BrowInnerUp] = FT_BROW_INNER_UP_RIGHT;
        arkit_to_unified[ARKit::BlendShape::BrowOuterUpRight] = FT_BROW_OUTER_UP_RIGHT;
        arkit_to_unified[ARKit::BlendShape::BrowOuterUpLeft] = FT_BROW_OUTER_UP_LEFT;
        arkit_to_unified[ARKit::BlendShape::NoseSneerRight] = FT_NOSE_SNEER_RIGHT;
        arkit_to_unified[ARKit::BlendShape::NoseSneerLeft] = FT_NOSE_SNEER_LEFT;
        arkit_to_unified[ARKit::BlendShape::CheekSquintRight] = FT_CHEEK_SQUINT_RIGHT;
        arkit_to_unified[ARKit::BlendShape::CheekSquintLeft] = FT_CHEEK_SQUINT_LEFT;
        arkit_to_unified[ARKit::BlendShape::CheekPuff] = FT_CHEEK_PUFF_RIGHT;
        arkit_to_unified[ARKit::BlendShape::JawOpen] = FT_JAW_OPEN;
        arkit_to_unified[ARKit::BlendShape::MouthClose] = FT_MOUTH_CLOSED;
        arkit_to_unified[ARKit::BlendShape::JawRight] = FT_JAW_RIGHT;
        arkit_to_unified[ARKit::BlendShape::JawLeft] = FT_JAW_LEFT;
        arkit_to_unified[ARKit::BlendShape::JawForward] = FT_JAW_FORWARD;
        arkit_to_unified[ARKit::BlendShape::MouthRollUpper] = FT_LIP_SUCK_UPPER_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthRollLower] = FT_LIP_SUCK_LOWER_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthFunnel] = FT_LIP_FUNNEL_UPPER_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthPucker] = FT_LIP_PUCKER_UPPER_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthPucker] = FT_MOUTH_UPPER_UP_RIGHT;  // 2 NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthUpperUpLeft] = FT_MOUTH_UPPER_UP_LEFT; // 2 NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthLowerDownRight] = FT_MOUTH_LOWER_DOWN_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthLowerDownLeft] = FT_MOUTH_LOWER_DOWN_LEFT;
        arkit_to_unified[ARKit::BlendShape::MouthRight] = FT_MOUTH_UPPER_RIGHT; // NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthLeft] = FT_MOUTH_UPPER_LEFT; // NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthSmileRight] = FT_MOUTH_CORNER_PULL_RIGHT; // NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthSmileLeft] = FT_MOUTH_CORNER_PULL_LEFT; // NOTE = not in official mapping
        arkit_to_unified[ARKit::BlendShape::MouthFrownRight] = FT_MOUTH_FROWN_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthFrownLeft] = FT_MOUTH_FROWN_LEFT;
        arkit_to_unified[ARKit::BlendShape::MouthStretchRight] = FT_MOUTH_STRETCH_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthStretchLeft] = FT_MOUTH_STRETCH_LEFT;
        arkit_to_unified[ARKit::BlendShape::MouthDimpleRight] = FT_MOUTH_DIMPLE_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthDimpleLeft] = FT_MOUTH_DIMPLE_LEFT;
        arkit_to_unified[ARKit::BlendShape::MouthShrugUpper] = FT_MOUTH_RAISER_UPPER;
        arkit_to_unified[ARKit::BlendShape::MouthShrugLower] = FT_MOUTH_RAISER_LOWER;
        arkit_to_unified[ARKit::BlendShape::MouthPressRight] = FT_MOUTH_PRESS_RIGHT;
        arkit_to_unified[ARKit::BlendShape::MouthPressLeft] = FT_MOUTH_PRESS_LEFT;
        arkit_to_unified[ARKit::BlendShape::TongueOut] = FT_TONGUE_OUT;
    }
}