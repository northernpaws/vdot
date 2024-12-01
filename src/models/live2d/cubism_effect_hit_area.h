// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_HIT_AREA_H
#define VDOT_CUBISM_EFFECT_HIT_AREA_H

#include "cubism.h"

#include <CubismDefaultParameterId.hpp>
#include <CubismFramework.hpp>
#include <Id/CubismIdManager.hpp>

#include "cubism_effect.h"
#include "renderer/cubism_model_proxy.h"

class CubismEffectHitArea : public CubismEffect {
    GDCLASS( CubismEffectHitArea, CubismEffect )

  protected:
    static void _bind_methods() {
        godot::ClassDB::bind_method( godot::D_METHOD( "set_target", "target" ),
                                     &CubismEffectHitArea::set_target );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_target" ),
                                     &CubismEffectHitArea::get_target );

        godot::ClassDB::bind_method( godot::D_METHOD( "get_detail", "model", "id" ),
                                     &CubismEffectHitArea::get_detail );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_monitoring", "value" ),
                                     &CubismEffectHitArea::set_monitoring );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_monitoring" ),
                                     &CubismEffectHitArea::get_monitoring );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::BOOL, "monitoring" ), "set_monitoring",
                      "get_monitoring" );

        ADD_SIGNAL( godot::MethodInfo( SIGNAL_EFFECT_HIT_AREA_ENTERED,
                                       godot::PropertyInfo( godot::Variant::OBJECT, "model",
                                                            godot::PROPERTY_HINT_RESOURCE_TYPE,
                                                            "GDCubismUserModel" ),
                                       godot::PropertyInfo( godot::Variant::STRING, "id" ) ) );
        ADD_SIGNAL( godot::MethodInfo( SIGNAL_EFFECT_HIT_AREA_EXITED,
                                       godot::PropertyInfo( godot::Variant::OBJECT, "model",
                                                            godot::PROPERTY_HINT_RESOURCE_TYPE,
                                                            "GDCubismUserModel" ),
                                       godot::PropertyInfo( godot::Variant::STRING, "id" ) ) );
    }

  private:
    godot::Vector2 _target;
    bool _initialized = false;
    bool _target_update = false;
    bool _monitoring = true;
    godot::Dictionary _dict_monitoring;

    static godot::Rect2 build_rect2( const godot::Ref<godot::ArrayMesh> &ref_ary_mesh ) {
        godot::Array ary = ref_ary_mesh->surface_get_arrays( 0 );
        godot::PackedVector2Array ary_vtx = ary[godot::Mesh::ARRAY_VERTEX];
        const int64_t vtx_count = ary_vtx.size();

        godot::Rect2 check_rect( ary_vtx[0].x, ary_vtx[0].y, 0, 0 );

        for ( int64_t i = 1; i < vtx_count; i++ ) {
            check_rect.expand_to( ary_vtx[static_cast<int>( i )] );
        }

        return check_rect;
    }

    [[nodiscard]] godot::Array check_collide_triangle(
        const godot::Ref<godot::ArrayMesh> &ref_ary_mesh ) const {
        if ( ref_ary_mesh->surface_get_primitive_type( 0 ) != godot::Mesh::PRIMITIVE_TRIANGLES ) {
            return {};
        }

        godot::Array ary = ref_ary_mesh->surface_get_arrays( 0 );
        godot::PackedVector2Array ary_vtx = ary[godot::Mesh::ARRAY_VERTEX];
        godot::PackedInt32Array ary_idx = ary[godot::Mesh::ARRAY_INDEX];

        godot::Array ary_result;

        for ( int64_t i = 0; i < ary_idx.size(); i += 3 ) {
            const int32_t ia = ary_idx[static_cast<int>( i ) + 0];
            const int32_t ib = ary_idx[static_cast<int>( i ) + 1];
            const int32_t ic = ary_idx[static_cast<int>( i ) + 2];

            const godot::Vector2 ab = ary_vtx[ib] - ary_vtx[ia];
            const godot::Vector2 bc = ary_vtx[ic] - ary_vtx[ib];
            const godot::Vector2 ca = ary_vtx[ia] - ary_vtx[ic];
            const godot::Vector2 ax = this->_target - ary_vtx[ia];
            const godot::Vector2 bx = this->_target - ary_vtx[ib];
            const godot::Vector2 cx = this->_target - ary_vtx[ic];

            if ( ( ab.cross( ax ) * bc.cross( bx ) ) > 0.0 ) {
                if ( ( bc.cross( bx ) * ca.cross( cx ) ) > 0.0 ) {
                    ary_result.append( ary_vtx[ia] );
                    ary_result.append( ary_vtx[ib] );
                    ary_result.append( ary_vtx[ic] );
                    break;
                }
            }
        }

        return ary_result;
    }

  public:
    void set_target( const godot::Vector2 &target ) {
        this->_target = target;
        this->_target_update = true;
    }
    godot::Vector2 get_target() const {
        return this->_target;
    }

    godot::Dictionary get_detail( const CubismModel *model, const godot::String &id ) {
        if ( !this->_initialized ) {
            return {};
        }
        if ( model == nullptr ) {
            return {};
        }
        if ( !model->is_initialized() ) {
            return {};
        }

        const godot::Dictionary dict_mesh = model->get_meshes();
        if ( dict_mesh.is_empty() ) {
            return {};
        }

        godot::Ref<godot::ArrayMesh> ref_ary_mesh = dict_mesh[id];
        if ( ref_ary_mesh.is_null() ) {
            return {};
        }
        if ( ref_ary_mesh->surface_get_array_index_len( 0 ) < 3 ) {
            return {};
        }

        godot::Dictionary dict_result;

        godot::Rect2 rect = build_rect2( ref_ary_mesh );
        dict_result["rect"] = rect;

        if ( rect.has_point( this->_target ) ) {
            godot::Array vertices = this->check_collide_triangle( ref_ary_mesh );
            if ( vertices.size() == 3 ) {
                dict_result["vertices"] = vertices;
            }
        }

        return dict_result;
    }

    void set_monitoring( const bool &value ) {
        this->_dict_monitoring.clear();
        this->_monitoring = value;
    }

    [[nodiscard]] bool get_monitoring() const {
        return this->_monitoring;
    }

    void _cubism_init( CubismModelProxy *internal_model ) override {
        if ( internal_model == nullptr ) {
            return;
        }
        this->_dict_monitoring.clear();
        this->_target_update = false;
        this->_initialized = true;
    }

    void _cubism_term( CubismModelProxy *internal_model ) override {
        this->_initialized = false;
    }

    void _cubism_process( CubismModelProxy *model, const float delta ) override {
        if ( !this->_active ) {
            return;
        }

        godot::Array ary = model->_owner_viewport->get_hit_areas();
        godot::Dictionary dict_mesh = model->_owner_viewport->get_meshes();

        for ( int64_t i = 0; i < ary.size(); i++ ) {
            const godot::String id = static_cast<godot::Dictionary>( ary[static_cast<int>( i )] )
                                         .get( "id", godot::String() );
            if ( !dict_mesh.has( id ) ) {
                continue;
            }

            godot::Ref<godot::ArrayMesh> ref_ary_mesh = dict_mesh[id];
            if ( ref_ary_mesh->surface_get_array_index_len( 0 ) < 3 ) {
                continue;
            }

            godot::Rect2 check_rect = CubismEffectHitArea::build_rect2( ref_ary_mesh );

            if ( this->_target_update && check_rect.has_point( this->_target ) ) {
                if ( this->_monitoring ) {
                    if ( !static_cast<bool>( this->_dict_monitoring.get( id, false ) ) ) {
                        this->emit_signal( SIGNAL_EFFECT_HIT_AREA_ENTERED, model->_owner_viewport,
                                           id );
                    }
                } else {
                    this->emit_signal( SIGNAL_EFFECT_HIT_AREA_ENTERED, model->_owner_viewport, id );
                }
                this->_dict_monitoring[id] = true;
            } else {
                if ( static_cast<bool>( this->_dict_monitoring.get( id, false ) ) ) {
                    this->emit_signal( SIGNAL_EFFECT_HIT_AREA_EXITED, model->_owner_viewport, id );
                }
                this->_dict_monitoring[id] = false;
            }
        }
    }

    void _cubism_epilogue( CubismModelProxy *model, const float delta ) override {
        this->_target_update = false;
    }
};

#endif // VDOT_CUBISM_EFFECT_HIT_AREA_H
