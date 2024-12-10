

#ifndef VDOT_MODEL_PARAMETER_H
#define VDOT_MODEL_PARAMETER_H

#include <godot_cpp/classes/resource.hpp>

/**
 * Provides a handle to access a specific parameter for a model.
 *
 * This is a high-level method of allowing various model implementations to expose parameters,
 *  that can then be mapped as output parameters to various input parameters.
 */
// NOTE: implemented as a resource so that it supports saving/loading parameter values.
class ModelParameter : public godot::Resource {
    GDCLASS( ModelParameter, godot::Resource )
  protected:
    godot::StringName parameter_id; // unique for the model

    godot::String parameter_name;        // user-friendly name
    godot::String parameter_description; // user-friendly description

    float parameter_minimum = 0.0f;
    float parameter_maximum = 1.0f;

    float parameter_default = 0.0f;

    float parameter_value = 0.0f;

    static void _bind_methods();

  public:
    [[nodiscard]] godot::StringName get_parameter_id() const;

    [[nodiscard]] godot::String get_parameter_name() const;
    [[nodiscard]] godot::String get_parameter_description() const;

    [[nodiscard]] float get_parameter_minimum_value() const;
    [[nodiscard]] float get_parameter_maximum_value() const;

    [[nodiscard]] float get_parameter_default_value() const;

    [[nodiscard]] float get_parameter_value() const;
    void set_parameter_value( float value );
};


namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're undef'ed
    template <>
    class TypedArray<godot::Ref<ModelParameter>> : public Array {
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
    struct GetTypeInfo<TypedArray<godot::Ref<ModelParameter>>> {                                                                                                         \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, ModelParameter::get_class_static());
        }
    };

    template <>
    struct GetTypeInfo<const TypedArray<godot::Ref<ModelParameter>> &> {                                                                                                 \
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE, ModelParameter::get_class_static());
        }
    };
};

#endif // VDOT_MODEL_PARAMETER_H
