<h1 align="center" style="text-align: center;">
  VDot
</h1>

<p align="center" style="text-align: center;">
  Godot-based program and GDExtension for rendering, tracking, and lip-syncing various VTube models and environments.  
</p>

-----
## Dependencies

- Git 
- CMake <=3.22
- C/C++ Compiler (GCC, Clang, or MSVC)
- [Live2D Cubism SDK for Native](https://www.live2d.com/en/sdk/download/native/) (downloaded automatically by cmake)

## Developing

### Debugging

> To enable debugging the library within Godot on **MacOS**, you'll need to modify the entitlements of the Godot editor to allow the `com.apple.security.get-task-allow` entitlement so that the debugger can attach to the process.
> ```bash
> $ codesign -s - --deep --force --options=runtime --entitlements ./editor.entitlements /Applications/Godot.app
> ```
> Note that this may cause a security signing warning the next time you start the Godot editor.

#### CLion

To debug the extension using CLion, start the Godot editor, open your project, and then in CLion debug the "Godot Editor" target.

## Credits

People and projects that helped make this possible.

> This section includes code and projects that may or may not have been used directly; this is clarified under each entry. I think it's important to credit people and projects that inspire any part of a project, no matter how small.

### Models

* [MizunagiKB](https://github.com/MizunagiKB) for [gd_cubism](https://github.com/MizunagiKB/gd_cubism) (MIT License)
  * Used as the foundation for the Live2D Cubism rendering components, including code, and shaders.
  * Modified to expose more settings, and to directly integrate face-tracking and lip-syncing support.

### Tracking

* tbxMb for [GodotLiveLinkFace](https://github.com/tbxMb/GodotLiveLinkFace/tree/main) (MIT License)
  * Project referenced to help model a C++ implementation of a [LiveLinkFace protocol](https://github.com/tbxMb/GodotLiveLinkFace/blob/main/doc/proto.md) server for receiving face tracking data from iPhone FaceID depth cameras.
  * Same [ARKit blendshape head model](http://filmicworlds.com/blog/solving-face-scans-for-arkit/) by John Hable (CC0) used for tracking preview panel in the editor. 
    * Downloaded the source models, extracted the mesh from `colin_dst_rig_shape_fit.fbx` (import into Godot, open the mesh -> "Actions..." -> "Set Mesh Save Paths" -> "Reimport"). Re-save as `.tres`, manually edit blend shape names in text editor, and resave.
* https://arkit-face-blendshapes.com 
  * Used as a development reference for mapping the output of ARKit feeds (i.e., LiveLinkFace server) to models.
  * This is a simplified view of the blend shapes from the [ARKit developer docs](https://developer.apple.com/documentation/arkit/arfaceanchor/blendshapelocation).
* MediaPipe face tracking.

## License

The code in this repository is governed under the [MIT license](LICENSE.md).

Components of this repository rely on software or SDKs with separate licenses, outlined in their sections below.

### Live2D Cubism

This repository has code that references the Live2D Cubism SDK which is governed under the following licenses.

 - **[Live2D Open Software License](https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html)**: Covers the Cubism Native Framework 
 - **[Live2D Proprietary Software License](https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html)**: Live2D Cubism Core, linked at build time

For more details, see the licensing section and file in the [Cubism Native Framework repository](https://github.com/Live2D/CubismNativeFramework/tree/develop). 
