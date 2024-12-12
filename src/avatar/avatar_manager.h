
#ifndef VDOT_AVATAR_MANAGER_H
#define VDOT_AVATAR_MANAGER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/hash_map.hpp>

/**
 * Root for managing avatars.
 */
class AvatarManager : public godot::Node {
    GDCLASS( AvatarManager, godot::Node )
  protected:
    static void _bind_methods();

  public:
};

#endif // VDOT_AVATAR_MANAGER_H
