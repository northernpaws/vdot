
#ifndef VDOT_LIVE2D_MODEL_BUNDLE_H
#define VDOT_LIVE2D_MODEL_BUNDLE_H

#include "models/model_bundle.h"

class Live2DModelBundle : public ModelBundle {
    GDCLASS( Live2DModelBundle, ModelBundle )
  protected:
    static void _bind_methods();
  public:

    /**
     * Packs the model bundle using the specified .model3.json file.
     *
     * This is a little more efficient then packing the entire directory
     * directly, as this will skip any files that aren't directly loaded
     * by the Live2D Cubism SDK.
     *
     * @param p_path - path to a .model3.json file.
     * @return an error or OK.
     */
    godot::Error pack_from_model3(const godot::String& p_path);
};

#endif // VDOT_LIVE2D_MODEL_H
