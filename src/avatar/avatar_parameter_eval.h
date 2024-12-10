

#ifndef VDOT_AVATAR_PARAMETER_EVAL_H
#define VDOT_AVATAR_PARAMETER_EVAL_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/object.hpp>

/**
 * Holds the evaluated value of an avatar parameter.
 */
class AvatarParameterEval : public godot::RefCounted {
    GDCLASS( AvatarParameterEval, godot::RefCounted )
  protected:
    static void _bind_methods();
  public:
    godot::StringName parameter_id;

    float input = 0.0f; // previous input
    float value = 0.0f;

    godot::StringName get_parameter_id() const;
    float get_parameter_input() const;
    float get_parameter_value() const;
};


namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're undef'ed
    template <>
    class TypedArray<AvatarParameterEval> : public Array {
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
    struct GetTypeInfo<AvatarParameterEval> {                                                                                                         \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, AvatarParameterEval::get_class_static());
        }
    };

    template <>
    struct GetTypeInfo<const AvatarParameterEval &> {                                                                                                 \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, AvatarParameterEval::get_class_static());
        }
    };
};

#endif // VDOT_AVATAR_PARAMETER_EVAL_H
