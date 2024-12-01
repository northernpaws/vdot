// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/viewport_texture.hpp>

#include <CubismFramework.hpp>
#include <Model/CubismModel.hpp>
#include <Rendering/CubismRenderer.hpp>

#include "cubism_model_proxy.h"
#include "cubism_renderer.h"

#include "cubism_renderer_2d.h"

godot::PackedInt32Array make_PackedArrayInt32( const Live2D::Cubism::Framework::csmUint16 *ptr,
                                               const int32_t &size );
godot::PackedVector2Array make_PackedArrayVector2( const Live2D::Cubism::Core::csmVector2 *ptr,
                                                   const int32_t &size );
godot::PackedVector2Array make_PackedArrayVector3( const Live2D::Cubism::Core::csmVector2 *ptr,
                                                   const int32_t &size,
                                                   const Csm::csmFloat32 &ppunit,
                                                   const godot::Vector2 &vct_adjust );
const godot::Vector4 make_vector4( const Live2D::Cubism::Core::csmVector4 &src_vec4 );

CubismRenderer2D::CubismRenderer2D() {
}

CubismRenderer2D::~CubismRenderer2D() {
}

godot::Ref<godot::ShaderMaterial> CubismRenderer2D::make_ShaderMaterial(
    const Csm::CubismModel *model, const Csm::csmInt32 index, const ::CubismRenderer &res ) const {
    godot::Ref<godot::ShaderMaterial> mat;
    mat.instantiate();

    CubismShader e = CUBISM_SHADER_NORM_MIX;

    if ( model->GetDrawableMaskCounts()[index] == 0 ) {
        switch ( model->GetDrawableBlendMode( index ) ) {
            case CubismBlendMode_Additive:
                e = CUBISM_SHADER_NORM_ADD;
                break;
            case CubismBlendMode_Normal:
                e = CUBISM_SHADER_NORM_MIX;
                break;
            case CubismBlendMode_Multiplicative:
                e = CUBISM_SHADER_NORM_MUL;
                break;
            default:
                e = CUBISM_SHADER_NORM_MIX;
                break;
        }
    } else {
        if ( model->GetDrawableInvertedMask( index ) == false ) {
            switch ( model->GetDrawableBlendMode( index ) ) {
                case CubismBlendMode_Additive:
                    e = CUBISM_SHADER_MASK_ADD;
                    break;
                case CubismBlendMode_Normal:
                    e = CUBISM_SHADER_MASK_MIX;
                    break;
                case CubismBlendMode_Multiplicative:
                    e = CUBISM_SHADER_MASK_MUL;
                    break;
                default:
                    e = CUBISM_SHADER_MASK_MIX;
                    break;
            }
        } else {
            switch ( model->GetDrawableBlendMode( index ) ) {
                case CubismBlendMode_Additive:
                    e = CUBISM_SHADER_MASK_ADD_INV;
                    break;
                case CubismBlendMode_Normal:
                    e = CUBISM_SHADER_MASK_MIX_INV;
                    break;
                case CubismBlendMode_Multiplicative:
                    e = CUBISM_SHADER_MASK_MUL_INV;
                    break;
                default:
                    e = CUBISM_SHADER_MASK_MIX_INV;
                    break;
            }
        }
    }

    godot::Ref<godot::Shader> shader = res._owner_viewport->get_shader( e );
    if ( shader.is_null() ) {
        shader = res.get_shader( e );
    }

    mat->set_shader( shader );

    const CubismTextureColor color_base =
        this->GetModelColorWithOpacity( model->GetDrawableOpacity( index ) );

    mat->set_shader_parameter(
        "color_base", godot::Vector4( color_base.R, color_base.G, color_base.B, color_base.A ) );
    mat->set_shader_parameter( "color_screen",
                               make_vector4( model->GetDrawableScreenColor( index ) ) );
    mat->set_shader_parameter( "color_multiply",
                               make_vector4( model->GetDrawableMultiplyColor( index ) ) );
    mat->set_shader_parameter( "channel", godot::Vector4( 0.0, 0.0, 0.0, 1.0 ) );
    mat->set_shader_parameter( "tex_main",
                               res.ary_texture[model->GetDrawableTextureIndex( index )] );

    return mat;
}

void CubismRenderer2D::make_ArrayMesh_prepare( const Csm::CubismModel *model,
                                               ::CubismRenderer &res ) {
    const godot::Vector2 vct_size = this->get_size( model );
    const godot::Vector2 vct_origin = this->get_origin( model );
    const float ppunit = this->get_ppunit( model );

    res.vct_canvas_size = res._owner_viewport->get_size();

    if ( res._owner_viewport->mask_viewport_size.x > 0 &&
         res._owner_viewport->mask_viewport_size.y > 0 ) {
        res.vct_mask_size = res._owner_viewport->mask_viewport_size;
    } else {
        res.vct_mask_size = res._owner_viewport->get_size();
    }

    res.CALCULATED_ORIGIN_C = ( godot::Vector2( res.vct_canvas_size ) * vct_origin ) / vct_size;
    res.CALCULATED_ORIGIN_M = ( godot::Vector2( res.vct_mask_size ) * vct_origin ) / vct_size;
    res.RATIO = float( res.vct_mask_size.x ) / float( res.vct_canvas_size.x );

    if ( res._owner_viewport->auto_scale == true ) {
        float fdstC = godot::MIN( static_cast<float>( res.vct_canvas_size.x ),
                                  static_cast<float>( res.vct_canvas_size.y ) );
        float fdstM = godot::MIN( static_cast<float>( res.vct_mask_size.x ),
                                  static_cast<float>( res.vct_mask_size.y ) );
        float fsrc = godot::MAX( vct_size.x, vct_size.y );

        res.CALCULATED_PPUNIT_C = ( fdstC * ppunit ) / fsrc;
        res.CALCULATED_PPUNIT_M = ( fdstM * ppunit ) / fsrc;
    } else {
        res.CALCULATED_PPUNIT_C = ppunit;
        res.CALCULATED_PPUNIT_M = ppunit * res.RATIO;
    }
}

godot::Ref<godot::ArrayMesh> CubismRenderer2D::make_ArrayMesh( const Csm::CubismModel *model,
                                                               const Csm::csmInt32 index,
                                                               const bool maskmode,
                                                               const ::CubismRenderer &res ) const {
    const godot::Vector2 adjust_pos = res.adjust_pos;
    godot::Array ary;

    ary.resize( godot::Mesh::ARRAY_MAX );

    if ( maskmode == true ) {
        if ( res._owner_viewport->auto_scale == true ) {
            ary[godot::Mesh::ARRAY_VERTEX] = make_PackedArrayVector3(
                model->GetDrawableVertexPositions( index ), model->GetDrawableVertexCount( index ),
                res.CALCULATED_PPUNIT_M, res.CALCULATED_ORIGIN_M + adjust_pos * res.RATIO );
        } else {
            ary[godot::Mesh::ARRAY_VERTEX] = make_PackedArrayVector3(
                model->GetDrawableVertexPositions( index ), model->GetDrawableVertexCount( index ),
                res.CALCULATED_PPUNIT_M * res.adjust_scale,
                res.CALCULATED_ORIGIN_M + adjust_pos * res.RATIO );
        }
    } else {
        ary[godot::Mesh::ARRAY_VERTEX] = make_PackedArrayVector3(
            model->GetDrawableVertexPositions( index ), model->GetDrawableVertexCount( index ),
            res.CALCULATED_PPUNIT_C * res.adjust_scale, res.CALCULATED_ORIGIN_C + res.adjust_pos );
    }

    ary[godot::Mesh::ARRAY_TEX_UV] = make_PackedArrayVector2(
        model->GetDrawableVertexUvs( index ), model->GetDrawableVertexCount( index ) );

    ary[godot::Mesh::ARRAY_INDEX] = make_PackedArrayInt32(
        model->GetDrawableVertexIndices( index ), model->GetDrawableVertexIndexCount( index ) );

    godot::Ref<godot::ArrayMesh> ary_mesh;

    ary_mesh.instantiate();
    ary_mesh->add_surface_from_arrays( godot::Mesh::PRIMITIVE_TRIANGLES, ary );

    return ary_mesh;
}

Csm::csmInt32 CubismRenderer2D::calc_viewport_count() const {
    const Live2D::Cubism::Framework::CubismModel *model = this->GetModel();
    Csm::csmInt32 count = 0;

    for ( Csm::csmInt32 index = 0; index < model->GetDrawableCount(); index++ ) {
        if ( model->GetDrawableMaskCounts()[index] > 0 ) {
            count++;
        }
    }

    return count;
}

Csm::csmInt32 CubismRenderer2D::calc_mesh_instance_count() const {
    const Live2D::Cubism::Framework::CubismModel *model = this->GetModel();
    Csm::csmInt32 count = 0;

    for ( Csm::csmInt32 index = 0; index < model->GetDrawableCount(); index++ ) {
        count += model->GetDrawableMaskCounts()[index];
        count++;
    }

    return count;
}

godot::Vector2 CubismRenderer2D::get_size( const Csm::CubismModel *model ) const {
    Live2D::Cubism::Core::csmVector2 vct_size;
    Live2D::Cubism::Core::csmVector2 vct_origin;
    Csm::csmFloat32 ppunit;

    Live2D::Cubism::Core::csmReadCanvasInfo( model->GetModel(), &vct_size, &vct_origin, &ppunit );

    return godot::Vector2( vct_size.X, vct_size.Y );
}

godot::Vector2 CubismRenderer2D::get_origin( const Csm::CubismModel *model ) const {
    Live2D::Cubism::Core::csmVector2 vct_size;
    Live2D::Cubism::Core::csmVector2 vct_origin;
    Csm::csmFloat32 ppunit;

    Live2D::Cubism::Core::csmReadCanvasInfo( model->GetModel(), &vct_size, &vct_origin, &ppunit );

    return godot::Vector2( vct_origin.X, vct_origin.Y );
}

float CubismRenderer2D::get_ppunit( const Csm::CubismModel *model ) const {
    Live2D::Cubism::Core::csmVector2 vct_size;
    Live2D::Cubism::Core::csmVector2 vct_origin;
    Csm::csmFloat32 ppunit;

    Live2D::Cubism::Core::csmReadCanvasInfo( model->GetModel(), &vct_size, &vct_origin, &ppunit );

    return ppunit;
}

void CubismRenderer2D::update_mask( godot::SubViewport *viewport, const Csm::csmInt32 index,
                                    ::CubismRenderer &res ) {
    Live2D::Cubism::Framework::CubismModel *model = this->GetModel();

    godot::Ref<godot::ShaderMaterial> mat;
    mat.instantiate();

    godot::Ref<godot::Shader> shader = res._owner_viewport->get_shader( CUBISM_SHADER_MASK );
    if ( shader.is_null() ) {
        shader = res.get_shader( CUBISM_SHADER_MASK );
    }

    mat->set_shader( shader );
    mat->set_shader_parameter( "channel", godot::Vector4( 0.0, 0.0, 0.0, 1.0 ) );
    mat->set_shader_parameter( "tex_main",
                               res.ary_texture[model->GetDrawableTextureIndex( index )] );

    for ( Csm::csmInt32 m_index = 0; m_index < model->GetDrawableMaskCounts()[index]; m_index++ ) {
        Csm::csmInt32 j = model->GetDrawableMasks()[index][m_index];
        godot::MeshInstance2D *node = res.request_mesh_instance();

        node->set_mesh( this->make_ArrayMesh( model, j, true, res ) );

        node->set_material( mat );
        node->set_z_index( model->GetDrawableRenderOrders()[index] );
        node->set_visible( true );

        viewport->add_child( node );
    }
}

void CubismRenderer2D::update( ::CubismRenderer &res ) {
    const Live2D::Cubism::Framework::CubismModel *model = this->GetModel();
    const Csm::csmInt32 *renderOrder = model->GetDrawableRenderOrders();

    this->make_ArrayMesh_prepare( model, res );

    // 描画
    for ( Csm::csmInt32 index = 0; index < model->GetDrawableCount(); index++ ) {
        // Drawableが表示状態でなければ処理をパスする
        if ( model->GetDrawableDynamicFlagIsVisible( index ) == false ) {
            continue;
        }
        if ( model->GetDrawableVertexCount( index ) == 0 ) {
            continue;
        }
        if ( model->GetDrawableVertexIndexCount( index ) == 0 ) {
            continue;
        }

        godot::MeshInstance2D *node = res.request_mesh_instance();
        godot::Ref<godot::ShaderMaterial> mat = this->make_ShaderMaterial( model, index, res );

        Live2D::Cubism::Framework::CubismIdHandle handle = model->GetDrawableId( index );
        godot::String node_name( handle->GetString().GetRawString() );

        if ( model->GetDrawableMaskCounts()[index] > 0 ) {
            godot::SubViewport *viewport = res.request_viewport();

            viewport->set_size( res.vct_mask_size );

            viewport->set_disable_3d( true ); // SUBVIEWPORT_DISABLE_3D_FLAG
            viewport->set_clear_mode( godot::SubViewport::ClearMode::CLEAR_MODE_ALWAYS );
            // set_update_mode must be specified
            viewport->set_update_mode( godot::SubViewport::UpdateMode::UPDATE_ALWAYS );
            viewport->set_disable_input( true );
            // Memory leak when set_use_own_world_3d is true
            // https://github.com/godotengine/godot/issues/81476
            viewport->set_use_own_world_3d( false ); // SUBVIEWPORT_USE_OWN_WORLD_3D_FLAG
            // Memory leak when set_transparent_background is true(* every time & window minimize)
            // https://github.com/godotengine/godot/issues/89651
            viewport->set_transparent_background( true );

            this->update_mask( viewport, index, res );

            // res._parent_node->add_child(viewport);
            res._parent_node->call_deferred( "add_child", viewport );

            mat->set_shader_parameter( "tex_mask", viewport->get_texture() );

            mat->set_shader_parameter( "auto_scale", res._owner_viewport->auto_scale );
            mat->set_shader_parameter( "canvas_size", godot::Vector2( res.vct_canvas_size ) );
            mat->set_shader_parameter( "mask_size", godot::Vector2( res.vct_mask_size ) );
            mat->set_shader_parameter( "ratio", res.RATIO );
            mat->set_shader_parameter( "adjust_scale", res.adjust_scale );
            mat->set_shader_parameter( "adjust_pos", res.adjust_pos );
        }

        godot::Ref<godot::ArrayMesh> m = this->make_ArrayMesh( model, index, false, res );

        node->set_name( node_name );
        node->set_mesh( m );
        res.dict_mesh[node_name] = m;
        node->set_material( mat );
        node->set_z_index( renderOrder[index] );
        node->set_visible( true );

        // res._parent_node->add_child(node);
        res._parent_node->call_deferred( "add_child", node );
    }
}

void CubismRenderer2D::update( ::CubismRenderer &res, const bool update_node,
                               const bool update_mesh ) {
    const Live2D::Cubism::Framework::CubismModel *model = this->GetModel();

    for ( Csm::csmInt32 index = 0; index < model->GetDrawableCount(); index++ ) {

        if ( model->GetDrawableDynamicFlagIsVisible( index ) == false ) {
            continue;
        }
        if ( model->GetDrawableVertexCount( index ) == 0 ) {
            continue;
        }
        if ( model->GetDrawableVertexIndexCount( index ) == 0 ) {
            continue;
        }

        Live2D::Cubism::Framework::CubismIdHandle handle = model->GetDrawableId( index );
        godot::String node_name( handle->GetString().GetRawString() );

        res.dict_mesh[node_name] = this->make_ArrayMesh( model, index, false, res );
    }
}

void CubismRenderer2D::Initialize( Csm::CubismModel *model, Csm::csmInt32 maskBufferCount ) {
    CubismRenderer::Initialize( model, maskBufferCount );
}

void CubismRenderer2D::DoDrawModel() {
}
void CubismRenderer2D::SaveProfile() {
}
void CubismRenderer2D::RestoreProfile() {
}

// ------------------------------------------------------------------ method(s)
godot::PackedInt32Array make_PackedArrayInt32( const Live2D::Cubism::Framework::csmUint16 *ptr,
                                               const int32_t &size ) {
    godot::PackedInt32Array ary;
    ary.resize( size );
    for ( int i = 0; i < size; i++ ) {
        ary.set( i, ptr[i] );
    }
    return ary;
}

godot::PackedVector2Array make_PackedArrayVector2( const Live2D::Cubism::Core::csmVector2 *ptr,
                                                   const int32_t &size ) {
    godot::PackedVector2Array ary;
    ary.resize( size );
    for ( int i = 0; i < size; i++ ) {
        ary.set( i, godot::Vector2( ptr[i].X, ptr[i].Y ) );
    }
    return ary;
}

godot::PackedVector2Array make_PackedArrayVector3( const Live2D::Cubism::Core::csmVector2 *ptr,
                                                   const int32_t &size,
                                                   const Csm::csmFloat32 &ppunit,
                                                   const godot::Vector2 &vct_adjust ) {
    godot::PackedVector2Array ary;
    ary.resize( size );
    for ( int i = 0; i < size; i++ ) {
        ary.set( i,
                 ( godot::Vector2( ptr[i].X, static_cast<real_t>( ptr[i].Y * -1.0 ) ) * ppunit ) +
                     vct_adjust );
    }
    return ary;
}

const godot::Vector4 make_vector4( const Live2D::Cubism::Core::csmVector4 &src_vec4 ) {
    return godot::Vector4( src_vec4.X, src_vec4.Y, src_vec4.Z, src_vec4.W );
}
