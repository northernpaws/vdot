

#ifndef VDOT_MODEL_2D_H
#define VDOT_MODEL_2D_H

#include "models/model.h"

/**
 * The base class for 2D-based VTuber models.
 */
class Model2D : public Model {
    GDCLASS( Model2D, Model )
  protected:
    static void _bind_methods();
};

#endif // VDOT_MODEL_2D_H
