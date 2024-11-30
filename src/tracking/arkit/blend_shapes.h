

#ifndef VDOT_BLEND_SHAPES_H
#define VDOT_BLEND_SHAPES_H

#include "godot_cpp/core/binder_common.hpp"

namespace ARKit {
    /**
     * BlendShapes defines an enum of all possible blend shape names used by ARKit's face tracking.
     *
     * Coincidentally, since this is primarily used by the LiveLinkFace server, the enum values
     * map to the corresponding blend shape value in a LiveLinkFace tracking packet.
     *
     * @see https://developer.apple.com/documentation/arkit/arfaceanchor/blendshapelocation
     * @see https://arkit-face-blendshapes.com
     */
    enum BlendShape {
        Unknown = 0,

        EyeBlinkLeft = 1,
        EyeLookDownLeft = 2,
        EyeLookInLeft = 3,
        EyeLookOutLeft = 4,
        EyeLookUpLeft = 5,
        EyeSquintLeft = 6,
        EyeWideLeft = 7,

        EyeBlinkRight = 8,
        EyeLookDownRight = 9,
        EyeLookInRight = 10,
        EyeLookOutRight = 11,
        EyeLookUpRight = 12,
        EyeSquintRight = 13,
        EyeWideRight = 14,

        JawForward = 15,
        JawRight = 16,
        JawLeft = 17,
        JawOpen = 18,

        MouthClose = 19,
        MouthFunnel = 20,
        MouthPucker = 21,
        MouthRight = 22,
        MouthLeft = 23,

        MouthSmileLeft = 24,
        MouthSmileRight = 25,

        MouthFrownLeft = 26,
        MouthFrownRight = 27,

        MouthDimpleLeft = 28,
        MouthDimpleRight = 29,

        MouthStretchLeft = 30,
        MouthStretchRight = 31,

        MouthRollLower = 32,
        MouthRollUpper = 33,
        MouthShrugLower = 34,
        MouthShrugUpper = 35,

        MouthPressLeft = 36,
        MouthPressRight = 37,

        MouthLowerDownLeft = 38,
        MouthLowerDownRight = 39,

        MouthUpperUpLeft = 40,
        MouthUpperUpRight = 41,

        BrowDownLeft = 42,
        BrowDownRight = 43,

        BrowInnerUp = 44,

        BrowOuterUpLeft = 45,
        BrowOuterUpRight = 46,

        CheekPuff = 47,

        CheekSquintLeft = 48,
        CheekSquintRight = 49,

        NoseSneerLeft = 50,
        NoseSneerRight = 51,

        TongueOut = 52,
    };
}

VARIANT_ENUM_CAST(ARKit::BlendShape);

#endif // VDOT_BLEND_SHAPES_H
