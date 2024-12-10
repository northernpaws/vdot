
#ifndef VDOT_AVATAR_H
#define VDOT_AVATAR_H

#include <godot_cpp/classes/sprite2d.hpp>

#include "avatar_parameter.h"

namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're undef'ed
    template <>
    class TypedArray<godot::Ref<AvatarParameter>> : public Array {
      public:
        _FORCE_INLINE_ void operator=(const Array &p_array) {
            ERR_FAIL_COND_MSG(!is_same_typed(p_array), "Cannot assign an array with a different element type.");
            _ref(p_array);
        }
        _FORCE_INLINE_ TypedArray(const Variant &p_variant) :
            TypedArray(Array(p_variant)) {
        }
        _FORCE_INLINE_ TypedArray(const Array &p_array) {
            set_typed(godot::Variant::Type::OBJECT, StringName(), Variant());
            if (is_same_typed(p_array)) {
                _ref(p_array);
            } else {
                assign(p_array);
            }
        }
        _FORCE_INLINE_ TypedArray() {
            set_typed(godot::Variant::Type::OBJECT, StringName(), Variant());
        }
    };

    template <>
    struct GetTypeInfo<TypedArray<godot::Ref<AvatarParameter>>> {                                                                                                         \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, Variant::get_type_name(godot::Variant::Type::OBJECT).utf8().get_data());
        }
    };

    template <>
    struct GetTypeInfo<const TypedArray<godot::Ref<AvatarParameter>> &> {                                                                                                 \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, Variant::get_type_name(godot::Variant::Type::OBJECT).utf8().get_data());
        }
    };
};

/**
 * The highest-level component for displaying a VTuber avatar.
 *
 * Encapsulates model rendering, motion tracking, parameters, etc.
 */
class Avatar : public godot::Sprite2D {
    GDCLASS( Avatar, godot::Sprite2D )
  protected:
    godot::TypedArray<godot::Ref<AvatarParameter>> parameters;

    static void _bind_methods();
  public:

    [[nodiscard]] godot::TypedArray<godot::Ref<AvatarParameter>> get_avatar_parameters() const;
    void set_avatar_parameters(const godot::TypedArray<godot::Ref<AvatarParameter>>& p_parameters);

};

#endif // VDOT_AVATAR_H
