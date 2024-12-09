

#ifndef VDOT_BLEND_SHAPES_H
#define VDOT_BLEND_SHAPES_H

#include "godot_cpp/core/binder_common.hpp"
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vmap.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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
        EyeBlinkLeft = 0,
        EyeLookDownLeft = 1,
        EyeLookInLeft = 2,
        EyeLookOutLeft = 3,
        EyeLookUpLeft = 4,
        EyeSquintLeft = 5,
        EyeWideLeft = 6,

        EyeBlinkRight = 7,
        EyeLookDownRight = 8,
        EyeLookInRight = 9,
        EyeLookOutRight = 10,
        EyeLookUpRight = 11,
        EyeSquintRight = 12,
        EyeWideRight = 13,

        JawForward = 14,
        JawRight = 15,
        JawLeft = 16,
        JawOpen = 17,

        MouthClose = 18,
        MouthFunnel = 19,
        MouthPucker = 20,
        MouthRight = 21,
        MouthLeft = 22,

        MouthSmileLeft = 23,
        MouthSmileRight = 24,

        MouthFrownLeft = 25,
        MouthFrownRight = 26,

        MouthDimpleLeft = 27,
        MouthDimpleRight = 28,

        MouthStretchLeft = 29,
        MouthStretchRight = 30,

        MouthRollLower = 31,
        MouthRollUpper = 32,
        MouthShrugLower = 33,
        MouthShrugUpper = 34,

        MouthPressLeft = 35,
        MouthPressRight = 36,

        MouthLowerDownLeft = 37,
        MouthLowerDownRight = 38,

        MouthUpperUpLeft = 39,
        MouthUpperUpRight = 40,

        BrowDownLeft = 41,
        BrowDownRight = 42,

        BrowInnerUp = 43,

        BrowOuterUpLeft = 44,
        BrowOuterUpRight = 45,

        CheekPuff = 46,

        CheekSquintLeft = 47,
        CheekSquintRight = 48,

        NoseSneerLeft = 49,
        NoseSneerRight = 50,

        TongueOut = 51,

        // limit used for array sizing.
        Max = 52,
    };

    static godot::HashMap<godot::String, BlendShape> ShapeNames;

    // helper called to populate the hashmap.
    void _init_arkit_shape_names();
}

VARIANT_ENUM_CAST( ARKit::BlendShape );

#endif // VDOT_BLEND_SHAPES_H
