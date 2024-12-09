

#ifndef VDOT_UNIFIED_EXPRESSIONS_H
#define VDOT_UNIFIED_EXPRESSIONS_H

#include <map>

#include "arkit_blend_shapes.h"

namespace UnifiedExpressions {
    /**
     * Enum constants for Unified Expressions base and blended shapes.
     *
     * These use the Unified Expressions blendshapes from VRCFaceTracking,
     *  adapted from Godot's experimental XR support driver.
     *
     * @see: https://docs.vrcft.io/docs/tutorial-avatars/tutorial-avatars-extras/unified-blendshapes
     * @see:
     * https://github.com/godotengine/godot/blob/eb5103093c1bfd4d527ec1255d28e9bc8d3625b5/servers/xr/xr_face_tracker.h#L49C2-L196C4
     */
    enum BlendShape {
        // Base Shapes
        FT_EYE_LOOK_OUT_RIGHT,       // Right eye looks outwards.
        FT_EYE_LOOK_IN_RIGHT,        // Right eye looks inwards.
        FT_EYE_LOOK_UP_RIGHT,        // Right eye looks upwards.
        FT_EYE_LOOK_DOWN_RIGHT,      // Right eye looks downwards.
        FT_EYE_LOOK_OUT_LEFT,        // Left eye looks outwards.
        FT_EYE_LOOK_IN_LEFT,         // Left eye looks inwards.
        FT_EYE_LOOK_UP_LEFT,         // Left eye looks upwards.
        FT_EYE_LOOK_DOWN_LEFT,       // Left eye looks downwards.
        FT_EYE_CLOSED_RIGHT,         // Closes the right eyelid.
        FT_EYE_CLOSED_LEFT,          // Closes the left eyelid.
        FT_EYE_SQUINT_RIGHT,         // Squeezes the right eye socket muscles.
        FT_EYE_SQUINT_LEFT,          // Squeezes the left eye socket muscles.
        FT_EYE_WIDE_RIGHT,           // Right eyelid widens beyond relaxed.
        FT_EYE_WIDE_LEFT,            // Left eyelid widens beyond relaxed.
        FT_EYE_DILATION_RIGHT,       // Dilates the right eye pupil.
        FT_EYE_DILATION_LEFT,        // Dilates the left eye pupil.
        FT_EYE_CONSTRICT_RIGHT,      // Constricts the right eye pupil.
        FT_EYE_CONSTRICT_LEFT,       // Constricts the left eye pupil.
        FT_BROW_PINCH_RIGHT,         // Right eyebrow pinches in.
        FT_BROW_PINCH_LEFT,          // Left eyebrow pinches in.
        FT_BROW_LOWERER_RIGHT,       // Outer right eyebrow pulls down.
        FT_BROW_LOWERER_LEFT,        // Outer left eyebrow pulls down.
        FT_BROW_INNER_UP_RIGHT,      // Inner right eyebrow pulls up.
        FT_BROW_INNER_UP_LEFT,       // Inner left eyebrow pulls up.
        FT_BROW_OUTER_UP_RIGHT,      // Outer right eyebrow pulls up.
        FT_BROW_OUTER_UP_LEFT,       // Outer left eyebrow pulls up.
        FT_NOSE_SNEER_RIGHT,         // Right side face sneers.
        FT_NOSE_SNEER_LEFT,          // Left side face sneers.
        FT_NASAL_DILATION_RIGHT,     // Right side nose canal dilates.
        FT_NASAL_DILATION_LEFT,      // Left side nose canal dilates.
        FT_NASAL_CONSTRICT_RIGHT,    // Right side nose canal constricts.
        FT_NASAL_CONSTRICT_LEFT,     // Left side nose canal constricts.
        FT_CHEEK_SQUINT_RIGHT,       // Raises the right side cheek.
        FT_CHEEK_SQUINT_LEFT,        // Raises the left side cheek.
        FT_CHEEK_PUFF_RIGHT,         // Puffs the right side cheek.
        FT_CHEEK_PUFF_LEFT,          // Puffs the left side cheek.
        FT_CHEEK_SUCK_RIGHT,         // Sucks in the right side cheek.
        FT_CHEEK_SUCK_LEFT,          // Sucks in the left side cheek.
        FT_JAW_OPEN,                 // Opens jawbone.
        FT_MOUTH_CLOSED,             // Closes the mouth.
        FT_JAW_RIGHT,                // Pushes jawbone right.
        FT_JAW_LEFT,                 // Pushes jawbone left.
        FT_JAW_FORWARD,              // Pushes jawbone forward.
        FT_JAW_BACKWARD,             // Pushes jawbone backward.
        FT_JAW_CLENCH,               // Flexes jaw muscles.
        FT_JAW_MANDIBLE_RAISE,       // Raises the jawbone.
        FT_LIP_SUCK_UPPER_RIGHT,     // Upper right lip part tucks in the mouth.
        FT_LIP_SUCK_UPPER_LEFT,      // Upper left lip part tucks in the mouth.
        FT_LIP_SUCK_LOWER_RIGHT,     // Lower right lip part tucks in the mouth.
        FT_LIP_SUCK_LOWER_LEFT,      // Lower left lip part tucks in the mouth.
        FT_LIP_SUCK_CORNER_RIGHT,    // Right lip corner folds into the mouth.
        FT_LIP_SUCK_CORNER_LEFT,     // Left lip corner folds into the mouth.
        FT_LIP_FUNNEL_UPPER_RIGHT,   // Upper right lip part pushes into a funnel.
        FT_LIP_FUNNEL_UPPER_LEFT,    // Upper left lip part pushes into a funnel.
        FT_LIP_FUNNEL_LOWER_RIGHT,   // Lower right lip part pushes into a funnel.
        FT_LIP_FUNNEL_LOWER_LEFT,    // Lower left lip part pushes into a funnel.
        FT_LIP_PUCKER_UPPER_RIGHT,   // Upper right lip part pushes outwards.
        FT_LIP_PUCKER_UPPER_LEFT,    // Upper left lip part pushes outwards.
        FT_LIP_PUCKER_LOWER_RIGHT,   // Lower right lip part pushes outwards.
        FT_LIP_PUCKER_LOWER_LEFT,    // Lower left lip part pushes outwards.
        FT_MOUTH_UPPER_UP_RIGHT,     // Upper right part of the lip pulls up.
        FT_MOUTH_UPPER_UP_LEFT,      // Upper left part of the lip pulls up.
        FT_MOUTH_LOWER_DOWN_RIGHT,   // Lower right part of the lip pulls up.
        FT_MOUTH_LOWER_DOWN_LEFT,    // Lower left part of the lip pulls up.
        FT_MOUTH_UPPER_DEEPEN_RIGHT, // Upper right lip part pushes in the cheek.
        FT_MOUTH_UPPER_DEEPEN_LEFT,  // Upper left lip part pushes in the cheek.
        FT_MOUTH_UPPER_RIGHT,        // Moves upper lip right.
        FT_MOUTH_UPPER_LEFT,         // Moves upper lip left.
        FT_MOUTH_LOWER_RIGHT,        // Moves lower lip right.
        FT_MOUTH_LOWER_LEFT,         // Moves lower lip left.
        FT_MOUTH_CORNER_PULL_RIGHT,  // Right lip corner pulls diagonally up and out.
        FT_MOUTH_CORNER_PULL_LEFT,   // Left lip corner pulls diagonally up and out.
        FT_MOUTH_CORNER_SLANT_RIGHT, // Right corner lip slants up.
        FT_MOUTH_CORNER_SLANT_LEFT,  // Left corner lip slants up.
        FT_MOUTH_FROWN_RIGHT,        // Right corner lip pulls down.
        FT_MOUTH_FROWN_LEFT,         // Left corner lip pulls down.
        FT_MOUTH_STRETCH_RIGHT,      // Mouth corner lip pulls out and down.
        FT_MOUTH_STRETCH_LEFT,       // Mouth corner lip pulls out and down.
        FT_MOUTH_DIMPLE_RIGHT,       // Right lip corner is pushed backwards.
        FT_MOUTH_DIMPLE_LEFT,        // Left lip corner is pushed backwards.
        FT_MOUTH_RAISER_UPPER,       // Raises and slightly pushes out the upper mouth.
        FT_MOUTH_RAISER_LOWER,       // Raises and slightly pushes out the lower mouth.
        FT_MOUTH_PRESS_RIGHT,        // Right side lips press and flatten together vertically.
        FT_MOUTH_PRESS_LEFT,         // Left side lips press and flatten together vertically.
        FT_MOUTH_TIGHTENER_RIGHT,    // Right side lips squeeze together horizontally.
        FT_MOUTH_TIGHTENER_LEFT,     // Left side lips squeeze together horizontally.
        FT_TONGUE_OUT,               // Tongue visibly sticks out of the mouth.
        FT_TONGUE_UP,                // Tongue points upwards.
        FT_TONGUE_DOWN,              // Tongue points downwards.
        FT_TONGUE_RIGHT,             // Tongue points right.
        FT_TONGUE_LEFT,              // Tongue points left.
        FT_TONGUE_ROLL,              // Sides of the tongue funnel, creating a roll.
        FT_TONGUE_BLEND_DOWN,        // Tongue arches up then down inside the mouth.
        FT_TONGUE_CURL_UP,           // Tongue arches down then up inside the mouth.
        FT_TONGUE_SQUISH,            // Tongue squishes together and thickens.
        FT_TONGUE_FLAT,              // Tongue flattens and thins out.
        FT_TONGUE_TWIST_RIGHT, // Tongue tip rotates clockwise, with the rest following gradually.
        FT_TONGUE_TWIST_LEFT,  // Tongue tip rotates counter-clockwise, with the rest following
                               // gradually.
        FT_SOFT_PALATE_CLOSE,  // Inner mouth throat closes.
        FT_THROAT_SWALLOW,     // The Adam's apple visibly swallows.
        FT_NECK_FLEX_RIGHT,    // Right side neck visibly flexes.
        FT_NECK_FLEX_LEFT,     // Left side neck visibly flexes.
        // Blended Shapes
        FT_EYE_CLOSED,        // Closes both eye lids.
        FT_EYE_WIDE,          // Widens both eye lids.
        FT_EYE_SQUINT,        // Squints both eye lids.
        FT_EYE_DILATION,      // Dilates both pupils.
        FT_EYE_CONSTRICT,     // Constricts both pupils.
        FT_BROW_DOWN_RIGHT,   // Pulls the right eyebrow down and in.
        FT_BROW_DOWN_LEFT,    // Pulls the left eyebrow down and in.
        FT_BROW_DOWN,         // Pulls both eyebrows down and in.
        FT_BROW_UP_RIGHT,     // Right brow appears worried.
        FT_BROW_UP_LEFT,      // Left brow appears worried.
        FT_BROW_UP,           // Both brows appear worried.
        FT_NOSE_SNEER,        // Entire face sneers.
        FT_NASAL_DILATION,    // Both nose canals dilate.
        FT_NASAL_CONSTRICT,   // Both nose canals constrict.
        FT_CHEEK_PUFF,        // Puffs both cheeks.
        FT_CHEEK_SUCK,        // Sucks in both cheeks.
        FT_CHEEK_SQUINT,      // Raises both cheeks.
        FT_LIP_SUCK_UPPER,    // Tucks in the upper lips.
        FT_LIP_SUCK_LOWER,    // Tucks in the lower lips.
        FT_LIP_SUCK,          // Tucks in both lips.
        FT_LIP_FUNNEL_UPPER,  // Funnels in the upper lips.
        FT_LIP_FUNNEL_LOWER,  // Funnels in the lower lips.
        FT_LIP_FUNNEL,        // Funnels in both lips.
        FT_LIP_PUCKER_UPPER,  // Upper lip part pushes outwards.
        FT_LIP_PUCKER_LOWER,  // Lower lip part pushes outwards.
        FT_LIP_PUCKER,        // Lips push outwards.
        FT_MOUTH_UPPER_UP,    // Raises the upper lips.
        FT_MOUTH_LOWER_DOWN,  // Lowers the lower lips.
        FT_MOUTH_OPEN,        // Mouth opens, revealing teeth.
        FT_MOUTH_RIGHT,       // Moves mouth right.
        FT_MOUTH_LEFT,        // Moves mouth left.
        FT_MOUTH_SMILE_RIGHT, // Right side of the mouth smiles.
        FT_MOUTH_SMILE_LEFT,  // Left side of the mouth smiles.
        FT_MOUTH_SMILE,       // Mouth expresses a smile.
        FT_MOUTH_SAD_RIGHT,   // Right side of the mouth expresses sadness.
        FT_MOUTH_SAD_LEFT,    // Left side of the mouth expresses sadness.
        FT_MOUTH_SAD,         // Mouth expresses sadness.
        FT_MOUTH_STRETCH,     // Mouth stretches.
        FT_MOUTH_DIMPLE,      // Lip corners dimple.
        FT_MOUTH_TIGHTENER,   // Mouth tightens.
        FT_MOUTH_PRESS,       // Mouth presses together.
        FT_MAX                // Maximum blend shape.
    };

    // Yes, these traits are a mess, but allow for compile-time static optimization
    //  of the conversions, while still maintaining a decent amount of readability.
    template <ARKit::BlendShape V> struct ToUnifiedExpression {
        // TODO: zero length default
        static constexpr BlendShape value[] = { FT_EYE_LOOK_OUT_RIGHT };
    };

    // Base Shapes
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookOutRight> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_OUT_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookInRight> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_IN_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookUpRight> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_UP_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookDownRight> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_DOWN_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookOutLeft> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_OUT_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookInLeft> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_IN_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookUpLeft> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_UP_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeLookDownLeft> {
        static constexpr BlendShape value[] = { FT_EYE_LOOK_DOWN_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeBlinkRight> {
        static constexpr BlendShape value[] = { FT_EYE_CLOSED_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeBlinkLeft> {
        static constexpr BlendShape value[] = { FT_EYE_CLOSED_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeSquintRight> {
        static constexpr BlendShape value[] = { FT_EYE_SQUINT_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeSquintLeft> {
        static constexpr BlendShape value[] = { FT_EYE_SQUINT_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeWideRight> {
        static constexpr BlendShape value[] = { FT_EYE_WIDE_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::EyeWideLeft> {
        static constexpr BlendShape value[] = { FT_EYE_WIDE_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::BrowDownRight> {
        static constexpr BlendShape value[] = { FT_BROW_PINCH_RIGHT, FT_BROW_LOWERER_RIGHT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::BrowDownLeft> {
        static constexpr BlendShape value[] = { FT_BROW_PINCH_LEFT, FT_BROW_LOWERER_LEFT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::BrowInnerUp> {
        static constexpr BlendShape value[] = { FT_BROW_INNER_UP_RIGHT, FT_BROW_INNER_UP_LEFT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::BrowOuterUpRight> {
        static constexpr BlendShape value[] = { FT_BROW_OUTER_UP_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::BrowOuterUpLeft> {
        static constexpr BlendShape value[] = { FT_BROW_OUTER_UP_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::NoseSneerRight> {
        static constexpr BlendShape value[] = { FT_NOSE_SNEER_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::NoseSneerLeft> {
        static constexpr BlendShape value[] = { FT_NOSE_SNEER_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::CheekSquintRight> {
        static constexpr BlendShape value[] = { FT_CHEEK_SQUINT_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::CheekSquintLeft> {
        static constexpr BlendShape value[] = { FT_CHEEK_SQUINT_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::CheekPuff> {
        static constexpr BlendShape value[] = { FT_CHEEK_PUFF_RIGHT, FT_CHEEK_PUFF_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::JawOpen> {
        static constexpr BlendShape value[] = { FT_JAW_OPEN };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthClose> {
        static constexpr BlendShape value[] = { FT_MOUTH_CLOSED };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::JawRight> {
        static constexpr BlendShape value[] = { FT_JAW_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::JawLeft> {
        static constexpr BlendShape value[] = { FT_JAW_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::JawForward> {
        static constexpr BlendShape value[] = { FT_JAW_FORWARD };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthRollUpper> {
        static constexpr BlendShape value[] = { FT_LIP_SUCK_UPPER_RIGHT, FT_LIP_SUCK_UPPER_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthRollLower> {
        static constexpr BlendShape value[] = { FT_LIP_SUCK_LOWER_RIGHT, FT_LIP_SUCK_LOWER_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthFunnel> {
        static constexpr BlendShape value[] = { FT_LIP_FUNNEL_UPPER_RIGHT, FT_LIP_FUNNEL_UPPER_LEFT,
                                                FT_LIP_FUNNEL_LOWER_RIGHT,
                                                FT_LIP_FUNNEL_LOWER_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthPucker> {
        static constexpr BlendShape value[] = { FT_LIP_PUCKER_UPPER_RIGHT, FT_LIP_PUCKER_UPPER_LEFT,
                                                FT_LIP_PUCKER_LOWER_RIGHT,
                                                FT_LIP_PUCKER_LOWER_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthUpperUpRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_UPPER_UP_RIGHT,
                                                FT_MOUTH_UPPER_DEEPEN_RIGHT };
    }; // 2 NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthUpperUpLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_UPPER_UP_LEFT,
                                                FT_MOUTH_UPPER_DEEPEN_LEFT };
    }; // 2 NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthLowerDownRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_LOWER_DOWN_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthLowerDownLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_LOWER_DOWN_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_UPPER_RIGHT, FT_MOUTH_LOWER_RIGHT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_UPPER_LEFT, FT_MOUTH_LOWER_LEFT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthSmileRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_CORNER_PULL_RIGHT,
                                                FT_MOUTH_CORNER_SLANT_RIGHT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthSmileLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_CORNER_PULL_LEFT,
                                                FT_MOUTH_CORNER_SLANT_LEFT };
    }; // NOTE = not in official mapping
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthFrownRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_FROWN_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthFrownLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_FROWN_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthStretchRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_STRETCH_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthStretchLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_STRETCH_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthDimpleRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_DIMPLE_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthDimpleLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_DIMPLE_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthShrugUpper> {
        static constexpr BlendShape value[] = { FT_MOUTH_RAISER_UPPER };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthShrugLower> {
        static constexpr BlendShape value[] = { FT_MOUTH_RAISER_LOWER };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthPressRight> {
        static constexpr BlendShape value[] = { FT_MOUTH_PRESS_RIGHT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::MouthPressLeft> {
        static constexpr BlendShape value[] = { FT_MOUTH_PRESS_LEFT };
    };
    template <> struct ToUnifiedExpression<ARKit::BlendShape::TongueOut> {
        static constexpr BlendShape value[] = { FT_TONGUE_OUT };
    };
    
    // Yes, these traits are a mess, but allow for compile-time static optimization
    //  of the conversions, while still maintaining a decent amount of readability.
    template <BlendShape S> struct ToARKit {
        // TODO: zero length default
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookOutRight };
    };
    
    // Base Shapes
    template <> struct ToARKit<BlendShape::FT_EYE_LOOK_OUT_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookOutRight };
    };
    template <> struct ToARKit<FT_EYE_LOOK_IN_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookInRight };
    };
    template <> struct ToARKit<FT_EYE_LOOK_UP_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookUpRight };
    };
    template <> struct ToARKit<FT_EYE_LOOK_DOWN_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookDownRight };
    };
    template <> struct ToARKit<FT_EYE_LOOK_OUT_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookOutLeft };
    };
    template <> struct ToARKit<FT_EYE_LOOK_IN_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookInLeft };
    };
    template <> struct ToARKit<FT_EYE_LOOK_UP_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookUpLeft };
    };
    template <> struct ToARKit<FT_EYE_LOOK_DOWN_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeLookDownLeft };
    };
    template <> struct ToARKit<FT_EYE_CLOSED_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeBlinkRight };
    };
    template <> struct ToARKit<FT_EYE_CLOSED_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeBlinkLeft };
    };
    template <> struct ToARKit<FT_EYE_SQUINT_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeSquintRight };
    };
    template <> struct ToARKit<FT_EYE_SQUINT_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeSquintLeft };
    };
    template <> struct ToARKit<FT_EYE_WIDE_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeWideRight };
    };
    template <> struct ToARKit<FT_EYE_WIDE_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::EyeWideLeft };
    };
    template <> struct ToARKit<FT_BROW_PINCH_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::BrowDownRight };
    };
    template <> struct ToARKit<FT_BROW_PINCH_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::BrowDownLeft };
    };
    template <> struct ToARKit<FT_BROW_INNER_UP_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::BrowInnerUp };
    };
    template <> struct ToARKit<FT_BROW_OUTER_UP_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::BrowOuterUpRight };
    };
    template <> struct ToARKit<FT_BROW_OUTER_UP_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::BrowOuterUpLeft };
    };
    template <> struct ToARKit<FT_NOSE_SNEER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::NoseSneerRight };
    };
    template <> struct ToARKit<FT_NOSE_SNEER_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::NoseSneerLeft };
    };
    template <> struct ToARKit<FT_CHEEK_SQUINT_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::CheekSquintRight };
    };
    template <> struct ToARKit<FT_CHEEK_SQUINT_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::CheekSquintLeft };
    };
    template <> struct ToARKit<FT_CHEEK_PUFF_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::CheekPuff }; // FT_CHEEK_PUFF_LEFT
    };
    template <> struct ToARKit<FT_JAW_OPEN> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::JawOpen };
    };
    template <> struct ToARKit<FT_MOUTH_CLOSED> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthClose };
    };
    template <> struct ToARKit<FT_JAW_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::JawRight };
    };
    template <> struct ToARKit<FT_JAW_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::JawLeft };
    };
    template <> struct ToARKit<FT_JAW_FORWARD> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::JawForward };
    };
    template <> struct ToARKit<FT_LIP_SUCK_UPPER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthRollUpper }; // FT_LIP_SUCK_UPPER_LEFT
    };
    template <> struct ToARKit<FT_LIP_SUCK_LOWER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthRollLower }; // FT_LIP_SUCK_LOWER_LEFT
    };
    template <> struct ToARKit<FT_LIP_FUNNEL_UPPER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthFunnel }; // TODO: FT_LIP_FUNNEL_UPPER_RIGHT, FT_LIP_FUNNEL_UPPER_LEFT,FT_LIP_FUNNEL_LOWER_RIGHT,FT_LIP_FUNNEL_LOWER_LEFT
    };
    template <> struct ToARKit<FT_LIP_PUCKER_UPPER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthPucker }; // TODO: FT_LIP_PUCKER_UPPER_RIGHT, FT_LIP_PUCKER_UPPER_LEFT, FT_LIP_PUCKER_LOWER_RIGHT, FT_LIP_PUCKER_LOWER_LEFT
    };
    template <> struct ToARKit<FT_MOUTH_UPPER_UP_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthUpperUpRight }; // FT_MOUTH_UPPER_DEEPEN_RIGHT
    }; // 2 NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_UPPER_UP_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthUpperUpLeft }; // FT_MOUTH_UPPER_DEEPEN_LEFT
    }; // 2 NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_LOWER_DOWN_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthLowerDownRight };
    };
    template <> struct ToARKit<FT_MOUTH_LOWER_DOWN_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthLowerDownLeft };
    };
    template <> struct ToARKit<FT_MOUTH_UPPER_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthRight }; // FT_MOUTH_LOWER_RIGHT
    }; // NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_UPPER_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthLeft }; // FT_MOUTH_LOWER_LEFT
    }; // NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_CORNER_PULL_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthSmileRight }; // FT_MOUTH_CORNER_SLANT_RIGHT
    }; // NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_CORNER_PULL_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthSmileLeft }; // FT_MOUTH_CORNER_SLANT_LEFT
    }; // NOTE = not in official mapping
    template <> struct ToARKit<FT_MOUTH_FROWN_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthFrownRight };
    };
    template <> struct ToARKit<FT_MOUTH_FROWN_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthFrownLeft };
    };
    template <> struct ToARKit<FT_MOUTH_STRETCH_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthStretchRight };
    };
    template <> struct ToARKit<FT_MOUTH_STRETCH_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthStretchLeft };
    };
    template <> struct ToARKit<FT_MOUTH_DIMPLE_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthDimpleRight };
    };
    template <> struct ToARKit<FT_MOUTH_DIMPLE_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthDimpleLeft };
    };
    template <> struct ToARKit<FT_MOUTH_RAISER_UPPER> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthShrugUpper };
    };
    template <> struct ToARKit<FT_MOUTH_RAISER_LOWER> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthShrugLower };
    };
    template <> struct ToARKit<FT_MOUTH_PRESS_RIGHT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthPressRight };
    };
    template <> struct ToARKit<FT_MOUTH_PRESS_LEFT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::MouthPressLeft };
    };
    template <> struct ToARKit<FT_TONGUE_OUT> {
        static constexpr ARKit::BlendShape value[] = { ARKit::BlendShape::TongueOut };
    };

    /**
     * Converts the provided ARKit blend shape to the equivalent unified expression blend shape.
     * @param blend_shape The ARKit blend shape to convert.
     * @return The equivalent Unified Expressions blend shape.
     */
    template <ARKit::BlendShape V>
    UnifiedExpressions::BlendShape arkit_to_unified_cast( ARKit::BlendShape blend_shape ) {
        return ToUnifiedExpression<V>::value;
    }

    /**
     * Converts the provided Unified Express blend shape to the equivalent ARKit blend shape.
     * @param blend_shape The Unified Expression blend shape to convert.
     * @return The equivalent ARKit blend shape.
     */
    template <BlendShape V>
    ARKit::BlendShape unified_to_arkit_cast( BlendShape blend_shape ) {
        return ToARKit<V>::value;
    }

    static godot::HashMap<BlendShape, godot::StringName> blend_shape_names;

    void _init_blend_shape_names();

    static godot::HashMap<BlendShape, ARKit::BlendShape> unified_to_arkit;
    static godot::HashMap<ARKit::BlendShape, BlendShape> arkit_to_unified;

    void _init_arkit_unified_mappings();
}

#endif // VDOT_UNIFIED_EXPRESSIONS_H
