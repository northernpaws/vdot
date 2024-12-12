

#ifndef VDOT_PARAMETER_INPUT_H
#define VDOT_PARAMETER_INPUT_H

#include <godot_cpp/classes/resource.hpp>

class InputParameter : public godot::Resource {
    GDCLASS( InputParameter, godot::Resource )
  protected:
    static void _bind_methods();

  public:
};

#endif // VDOT_PARAMETER_INPUT_H
