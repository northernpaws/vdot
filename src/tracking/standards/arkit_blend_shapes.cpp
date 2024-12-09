
#include "arkit_blend_shapes.h"

namespace ARKit {
    void _init_arkit_shape_names() {
        ShapeNames.reserve( BlendShape::Max );

        ShapeNames["EyeBlinkLeft"] = BlendShape::EyeBlinkLeft;
        ShapeNames["EyeLookDownLeft"] = BlendShape::EyeLookDownLeft;
        ShapeNames["EyeLookInLeft"] = BlendShape::EyeLookInLeft;
        ShapeNames["EyeLookOutLeft"] = BlendShape::EyeLookOutLeft;
        ShapeNames["EyeLookUpLeft"] = BlendShape::EyeLookUpLeft;
        ShapeNames["EyeSquintLeft"] = BlendShape::EyeSquintLeft;
        ShapeNames["EyeWideLeft"] = BlendShape::EyeWideLeft;

        ShapeNames["EyeBlinkRight"] = BlendShape::EyeBlinkRight;
        ShapeNames["EyeLookDownRight"] = BlendShape::EyeLookDownRight;
        ShapeNames["EyeLookInRight"] = BlendShape::EyeLookInRight;
        ShapeNames["EyeLookOutRight"] = BlendShape::EyeLookOutRight;
        ShapeNames["EyeLookUpRight"] = BlendShape::EyeLookUpRight;
        ShapeNames["EyeSquintRight"] = BlendShape::EyeSquintRight;
        ShapeNames["EyeWideRight"] = BlendShape::EyeWideRight;

        ShapeNames["JawForward"] = BlendShape::JawForward;
        ShapeNames["JawRight"] = BlendShape::JawRight;
        ShapeNames["JawLeft"] = BlendShape::JawLeft;
        ShapeNames["JawOpen"] = BlendShape::JawOpen;

        ShapeNames["MouthClose"] = BlendShape::MouthClose;
        ShapeNames["MouthFunnel"] = BlendShape::MouthFunnel;
        ShapeNames["MouthPucker"] = BlendShape::MouthPucker;
        ShapeNames["MouthRight"] = BlendShape::MouthRight;
        ShapeNames["MouthLeft"] = BlendShape::MouthLeft;

        ShapeNames["MouthSmileLeft"] = BlendShape::MouthSmileLeft;
        ShapeNames["MouthSmileRight"] = BlendShape::MouthSmileRight;

        ShapeNames["MouthFrownLeft"] = BlendShape::MouthFrownLeft;
        ShapeNames["MouthFrownRight"] = BlendShape::MouthFrownRight;

        ShapeNames["MouthDimpleLeft"] = BlendShape::MouthDimpleLeft;
        ShapeNames["MouthDimpleRight"] = BlendShape::MouthDimpleRight;

        ShapeNames["MouthStretchLeft"] = BlendShape::MouthStretchLeft;
        ShapeNames["MouthStretchRight"] = BlendShape::MouthStretchRight;

        ShapeNames["MouthRollLower"] = BlendShape::MouthRollLower;
        ShapeNames["MouthRollUpper"] = BlendShape::MouthRollUpper;
        ShapeNames["MouthShrugLower"] = BlendShape::MouthShrugLower;
        ShapeNames["MouthShrugUpper"] = BlendShape::MouthShrugUpper;

        ShapeNames["MouthPressLeft"] = BlendShape::MouthPressLeft;
        ShapeNames["MouthPressRight"] = BlendShape::MouthPressRight;

        ShapeNames["MouthLowerDownLeft"] = BlendShape::MouthLowerDownLeft;
        ShapeNames["MouthLowerDownRight"] = BlendShape::MouthLowerDownRight;

        ShapeNames["MouthUpperUpLeft"] = BlendShape::MouthUpperUpLeft;
        ShapeNames["MouthUpperUpRight"] = BlendShape::MouthUpperUpRight;

        ShapeNames["BrowDownLeft"] = BlendShape::BrowDownLeft;
        ShapeNames["BrowDownRight"] = BlendShape::BrowDownRight;

        ShapeNames["BrowInnerUp"] = BlendShape::BrowInnerUp;

        ShapeNames["BrowOuterUpLeft"] = BlendShape::BrowOuterUpLeft;
        ShapeNames["BrowOuterUpRight"] = BlendShape::BrowOuterUpRight;

        ShapeNames["CheekPuff"] = BlendShape::CheekPuff;

        ShapeNames["CheekSquintLeft"] = BlendShape::CheekSquintLeft;
        ShapeNames["CheekSquintRight"] = BlendShape::CheekSquintRight;

        ShapeNames["NoseSneerLeft"] = BlendShape::NoseSneerLeft;
        ShapeNames["NoseSneerRight"] = BlendShape::NoseSneerRight;

        ShapeNames["TongueOut"] = BlendShape::TongueOut;
    }
}