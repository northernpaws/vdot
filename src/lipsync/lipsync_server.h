

#ifndef VDOT_LIPSYNC_SERVER_H
#define VDOT_LIPSYNC_SERVER_H

#include "parameters/parameter_context.h"
#include <godot_cpp/classes/ref_counted.hpp>

class LipsyncServer : public godot::RefCounted {
    GDCLASS( LipsyncServer, godot::RefCounted )
  protected:
    static LipsyncServer *singleton;

    static void _bind_methods();

    godot::Ref<ParameterContext> param_context;

  public:
    static LipsyncServer *get_singleton();

    LipsyncServer();
    ~LipsyncServer() override;
};

#endif // VDOT_LIPSYNC_SERVER_H
