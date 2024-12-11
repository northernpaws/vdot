
#ifndef VDOT_AVATAR_MANAGER_H
#define VDOT_AVATAR_MANAGER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/hash_map.hpp>

class AvatarType : public godot::Resource {
    GDCLASS( AvatarType, godot::Resource )
  protected:
    godot::String name = "Unnamed Type";
    godot::String description = "Generic avatar type.";

    static void _bind_methods();

  public:
    [[nodiscard]] godot::String get_avatar_type_name() const;
    void set_avatar_type_name( const godot::String &p_name );

    [[nodiscard]] godot::String get_avatar_type_description() const;
    void set_avatar_type_description( const godot::String &p_description );
};

namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're
    // undef'ed
    template <> class TypedArray<AvatarType> : public Array {
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

    template <> struct GetTypeInfo<TypedArray<AvatarType>> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(
                Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                Variant::get_type_name( godot::Variant::OBJECT ).utf8().get_data() );
        }
    };

    template <> struct GetTypeInfo<const TypedArray<AvatarType> &> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info(
                Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                Variant::get_type_name( godot::Variant::OBJECT ).utf8().get_data() );
        }
    };
};

/**
 * Root for managing avatars.
 */
class AvatarManager : public godot::Node {
    GDCLASS( AvatarManager, godot::Node )
  protected:
    godot::TypedArray<AvatarType> avatar_types;

    static void _bind_methods();

  public:
    void set_avatar_types( const godot::TypedArray<AvatarType> &p_types );
    [[nodiscard]] godot::TypedArray<AvatarType> get_avatar_types() const;
};

#endif // VDOT_AVATAR_MANAGER_H
