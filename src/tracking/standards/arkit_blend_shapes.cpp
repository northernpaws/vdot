
#include "arkit_blend_shapes.h"

namespace ARKit {

    godot::HashMap<godot::StringName, BlendShape> ShapeNames;

    godot::HashMap<BlendShape, godot::StringName> shape_to_name;

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
        
        shape_to_name.clear();
        
        shape_to_name[BlendShape::EyeBlinkLeft] = "eyeBlinkLeft";
        shape_to_name[BlendShape::EyeLookDownLeft] = "eyeLookDownLeft";
        shape_to_name[BlendShape::EyeLookInLeft] = "eyeLookInLeft";
        shape_to_name[BlendShape::EyeLookOutLeft] = "eyeLookOutLeft";
        shape_to_name[BlendShape::EyeLookUpLeft] = "eyeLookUpLeft";
        shape_to_name[BlendShape::EyeSquintLeft] = "eyeSquintLeft";
        shape_to_name[BlendShape::EyeWideLeft] = "eyeWideLeft";

        shape_to_name[BlendShape::EyeBlinkRight] = "eyeBlinkRight";
        shape_to_name[BlendShape::EyeLookDownRight] = "eyeLookDownRight";
        shape_to_name[BlendShape::EyeLookInRight] = "eyeLookInRight";
        shape_to_name[BlendShape::EyeLookOutRight] = "eyeLookOutRight";
        shape_to_name[BlendShape::EyeLookUpRight] = "eyeLookUpRight";
        shape_to_name[BlendShape::EyeSquintRight] = "eyeSquintRight";
        shape_to_name[BlendShape::EyeWideRight] = "eyeWideRight";

        shape_to_name[BlendShape::JawForward] = "jawForward";
        shape_to_name[BlendShape::JawRight] = "jawRight";
        shape_to_name[BlendShape::JawLeft] = "jawLeft";
        shape_to_name[BlendShape::JawOpen] = "jawOpen";

        shape_to_name[BlendShape::MouthClose] = "mouthClose";
        shape_to_name[BlendShape::MouthFunnel] = "mouthFunnel";
        shape_to_name[BlendShape::MouthPucker] = "mouthPucker";
        shape_to_name[BlendShape::MouthRight] = "mouthRight";
        shape_to_name[BlendShape::MouthLeft] = "mouthLeft";

        shape_to_name[BlendShape::MouthSmileLeft] = "mouthSmileLeft";
        shape_to_name[BlendShape::MouthSmileRight] = "mouthSmileRight";

        shape_to_name[BlendShape::MouthFrownLeft] = "mouthFrownLeft";
        shape_to_name[BlendShape::MouthFrownRight] = "mouthFrownRight";

        shape_to_name[BlendShape::MouthDimpleLeft] = "mouthDimpleLeft";
        shape_to_name[BlendShape::MouthDimpleRight] = "mouthDimpleRight";

        shape_to_name[BlendShape::MouthStretchLeft] = "mouthStretchLeft";
        shape_to_name[BlendShape::MouthStretchRight] = "mouthStretchRight";

        shape_to_name[BlendShape::MouthRollLower] = "mouthRollLower";
        shape_to_name[BlendShape::MouthRollUpper] = "mouthRollUpper";
        shape_to_name[BlendShape::MouthShrugLower] = "mouthShrugLower";
        shape_to_name[BlendShape::MouthShrugUpper] = "mouthShrugUpper";

        shape_to_name[BlendShape::MouthPressLeft] = "mouthPressLeft";
        shape_to_name[BlendShape::MouthPressRight] = "mouthPressRight";

        shape_to_name[BlendShape::MouthLowerDownLeft] = "mouthLowerDownLeft";
        shape_to_name[BlendShape::MouthLowerDownRight] = "mouthLowerDownRight";

        shape_to_name[BlendShape::MouthUpperUpLeft] = "mouthUpperUpLeft";
        shape_to_name[BlendShape::MouthUpperUpRight] = "mouthUpperUpRight";

        shape_to_name[BlendShape::BrowDownLeft] = "browDownLeft";
        shape_to_name[BlendShape::BrowDownRight] = "browDownRight";

        shape_to_name[BlendShape::BrowInnerUp] = "browInnerUp";

        shape_to_name[BlendShape::BrowOuterUpLeft] = "browOuterUpLeft";
        shape_to_name[BlendShape::BrowOuterUpRight] = "browOuterUpRight";

        shape_to_name[BlendShape::CheekPuff] = "cheekPuff";

        shape_to_name[BlendShape::CheekSquintLeft] = "cheekSquintLeft";
        shape_to_name[BlendShape::CheekSquintRight] = "cheekSquintRight";

        shape_to_name[BlendShape::NoseSneerLeft] = "noseSneerLeft";
        shape_to_name[BlendShape::NoseSneerRight] = "noseSneerRight";

        shape_to_name[BlendShape::TongueOut] = "tongueOut";

    }
}