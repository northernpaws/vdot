#ifndef VDOT_H
#define VDOT_H

#include "godot_cpp/classes/object.hpp"

namespace godot
{
    class ClassDB;
};

class VDot : public godot::Object
{
    GDCLASS( VDot, godot::Object )

public:
    static godot::String version();
    static godot::String godotCPPVersion();

private:
    static void _bind_methods();
};

#endif // VDOT_H