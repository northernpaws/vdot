

#ifndef VDOT_PARAMETER_INPUT_H
#define VDOT_PARAMETER_INPUT_H

#include <godot_cpp/classes/resource.hpp>

#include "parameter.h"

class InputParameter : public Parameter {
    GDCLASS( InputParameter, Parameter )
  protected:
    static void _bind_methods();
  public:
    static constexpr const char * SIGNAL_VALUE_CHANGED = "value_changed";

    float parameter_value = 0.0f;

    [[nodiscard]] float get_parameter_value() const;
    void set_parameter_value( float value );
};

#endif // VDOT_PARAMETER_INPUT_H
