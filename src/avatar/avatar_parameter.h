

#ifndef VDOT_AVATAR_PARAMETER_H
#define VDOT_AVATAR_PARAMETER_H

#include <godot_cpp/classes/resource.hpp>

/**
 * Defines a n input->output parameter mapping associated with the avatar.
 */
class AvatarParameter : public godot::Resource {
    GDCLASS( AvatarParameter, godot::Resource )
  protected:
    godot::StringName parameter_id; // unique for the model

    godot::String parameter_name;        // user-friendly name
    godot::String parameter_description; // user-friendly description

    // NOTE: use 0-1 range by default as that's fairly standard.
    godot::Vector2 input_range = godot::Vector2( 0.0f, 1.0f );
    godot::Vector2 output_range = godot::Vector2( 0.0f, 1.0f );

    static void _bind_methods();

  public:
    [[nodiscard]] godot::StringName get_parameter_id() const;
    void set_parameter_id( const godot::StringName &p_id );

    [[nodiscard]] godot::String get_parameter_name() const;
    void set_parameter_name( const godot::String &p_name );

    [[nodiscard]] godot::String get_parameter_description() const;
    void set_parameter_description( const godot::String &p_description );

    godot::Vector2 get_input_range() const;
    void set_input_range( const godot::Vector2 &p_range );

    godot::Vector2 get_output_range() const;
    void set_output_range( const godot::Vector2 &p_range );

    float calculate_value( float p_input, double delta ) const;
};

namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're
    // undef'ed
    template <> class TypedArray<AvatarParameter> : public Array {
      public:
        _FORCE_INLINE_ void operator=( const Array &p_array ) {
            ERR_FAIL_COND_MSG( !is_same_typed( p_array ),
                               "Cannot assign an array with a different element type." );
            _ref( p_array );
        }
        _FORCE_INLINE_ TypedArray( const Variant &p_variant ) : TypedArray( Array( p_variant ) ) {
        }
        _FORCE_INLINE_ TypedArray( const Array &p_array ) {
            set_typed( godot::Variant::Type::OBJECT, StringName(), Variant() );
            if ( is_same_typed( p_array ) ) {
                _ref( p_array );
            } else {
                assign( p_array );
            }
        }
        _FORCE_INLINE_ TypedArray() {
            set_typed( godot::Variant::Type::OBJECT, StringName(), Variant() );
        }
    };

    template <> struct GetTypeInfo<TypedArray<AvatarParameter>> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       Variant::get_type_name(godot::Variant::OBJECT).utf8().get_data() );
        }
    };

    template <> struct GetTypeInfo<const TypedArray<AvatarParameter> &> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       Variant::get_type_name(godot::Variant::OBJECT).utf8().get_data() );
        }
    };
};

#endif // VDOT_AVATAR_PARAMETER_H
