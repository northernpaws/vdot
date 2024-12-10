
#ifndef VDOT_COLLABORATION_SESSION_H
#define VDOT_COLLABORATION_SESSION_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "avatar/avatar.h"

#include "collaboration_peer.h"

namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're
    // undef'ed
    template <> class TypedArray<Avatar> : public Array {
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

    template <> struct GetTypeInfo<TypedArray<Avatar>> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       Avatar::get_class_static() );
        }
    };

    template <> struct GetTypeInfo<const TypedArray<Avatar> &> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       Avatar::get_class_static() );
        }
    };
};

namespace godot {
    // TODO: Ideally we'd use MAKE_TYPED_ARRAY and MAKE_TYPED_ARRAY_INFO, but in C++ they're
    // undef'ed
    template <> class TypedArray<godot::Ref<CollaborationPeer>> : public Array {
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

    template <> struct GetTypeInfo<TypedArray<godot::Ref<CollaborationPeer>>> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       CollaborationPeer::get_class_static() );
        }
    };

    template <> struct GetTypeInfo<const TypedArray<godot::Ref<CollaborationPeer>> &> {
        static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_ARRAY;
        static constexpr GDExtensionClassMethodArgumentMetadata METADATA =
            GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
        static inline PropertyInfo get_class_info() {
            return make_property_info( Variant::Type::ARRAY, "", PROPERTY_HINT_ARRAY_TYPE,
                                       CollaborationPeer::get_class_static() );
        }
    };
};

class CollaborationSession : public godot::Node {
    GDCLASS( CollaborationSession, godot::Node )
  protected:
    godot::Ref<CollaborationPeer> local_peer;
    godot::HashMap<int, godot::Ref<CollaborationPeer>> remote_peers;

    // Avatars local to this device that are being shared to the session.
    godot::TypedArray<Avatar> local_avatars;

    static void _bind_methods();

  public:
    CollaborationSession();

    void _ready() override;

    godot::Error start_server(); // start a session server
    godot::Error connect_to_server( const godot::String &p_address, int p_port );

    void add_local_avatar( Avatar *p_avatar );
    void remove_local_avatar( Avatar *p_avatar );

    void _client_connected_to_server();
    void _client_connection_failed();
    void _client_server_disconnected();

    void _peer_connected( int id );
    void _peer_disconnected( int id );
};

#endif // VDOT_COLLABORATION_SESSION_H
