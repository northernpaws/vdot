// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#include <godot_cpp/classes/resource_loader.hpp>

#include <CubismFramework.hpp>
#include <Model/CubismModel.hpp>
#include <Rendering/CubismRenderer.hpp>

#include "../cubism_model.h"

#include "cubism_renderer.h"

void _recurisive_dispose_node( const godot::Node *parent_node, const bool node_release );

CubismRenderer::CubismRenderer( CubismModel *owner_viewport, godot::Node *parent_node ) :
    _owner_viewport( owner_viewport ), _parent_node( parent_node ), sub_viewport_counter( 0 ),
    mesh_instance_counter( 0 ), adjust_pos( 0.0, 0.0 ), adjust_scale( 1.0 ) {
    godot::ResourceLoader *res_loader = memnew( godot::ResourceLoader );

    this->ary_shader.resize( CUBISM_SHADER_MAX );

    this->ary_shader[CUBISM_SHADER_NORM_ADD] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_norm_add.gdshader" );
    this->ary_shader[CUBISM_SHADER_NORM_MIX] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_norm_mix.gdshader" );
    this->ary_shader[CUBISM_SHADER_NORM_MUL] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_norm_mul.gdshader" );

    this->ary_shader[CUBISM_SHADER_MASK] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask.gdshader" );

    this->ary_shader[CUBISM_SHADER_MASK_ADD] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_add.gdshader" );
    this->ary_shader[CUBISM_SHADER_MASK_ADD_INV] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_add_inv.gdshader" );
    this->ary_shader[CUBISM_SHADER_MASK_MIX] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_mix.gdshader" );
    this->ary_shader[CUBISM_SHADER_MASK_MIX_INV] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_mix_inv.gdshader" );
    this->ary_shader[CUBISM_SHADER_MASK_MUL] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_mul.gdshader" );
    this->ary_shader[CUBISM_SHADER_MASK_MUL_INV] =
        res_loader->load( "res://addons/vdot/live2d/shader/2d_cubism_mask_mul_inv.gdshader" );

    memdelete( res_loader );
}

CubismRenderer::~CubismRenderer() {
    this->clear();
    this->ary_shader.clear();
    this->_owner_viewport = nullptr;
    this->_parent_node = nullptr;
}

void CubismRenderer::clear() {
    this->dispose_node( true );
    this->ary_texture.clear();
    this->ary_sub_viewport.clear();
    this->ary_mesh_instance.clear();
}

godot::SubViewport *CubismRenderer::request_viewport() {
    const Csm::csmInt32 counter = this->sub_viewport_counter++;

    if ( counter < this->ary_sub_viewport.size() ) {
        return godot::Object::cast_to<godot::SubViewport>( this->ary_sub_viewport[counter] );
    } else {
        godot::SubViewport *viewport = memnew( godot::SubViewport );
        this->ary_sub_viewport.append( viewport );
        return viewport;
    }
};

godot::MeshInstance2D *CubismRenderer::request_mesh_instance() {
    const Csm::csmInt32 counter = this->mesh_instance_counter++;

    if ( counter < this->ary_mesh_instance.size() ) {
        return godot::Object::cast_to<godot::MeshInstance2D>( this->ary_mesh_instance[counter] );
    } else {
        godot::MeshInstance2D *node = memnew( godot::MeshInstance2D );
        this->ary_mesh_instance.append( node );
        return node;
    }
}

void CubismRenderer::pro_proc( const Csm::csmInt32 viewport_count,
                               const Csm::csmInt32 mesh_instance_count ) {
    this->dispose_node( false );
    this->dict_mesh.clear();
    this->sub_viewport_counter = 0;
    this->mesh_instance_counter = 0;
}

void CubismRenderer::epi_proc() {
}

void CubismRenderer::dispose_node( const bool node_release ) {
    _recurisive_dispose_node( this->_parent_node, node_release );
}

// ------------------------------------------------------------------ method(s)
void _recurisive_dispose_node( const godot::Node *parent_node, const bool node_release ) {

    godot::TypedArray<godot::Node> ary_node = parent_node->get_children();

    for ( Csm::csmInt32 i = 0; i < ary_node.size(); i++ ) {

        if ( godot::Object::cast_to<CubismEffect>( ary_node[i] ) != nullptr ) {
            continue;
        }

        auto *m_node = godot::Object::cast_to<godot::MeshInstance2D>( ary_node[i] );
        if ( m_node != nullptr ) {
            m_node->set_material( nullptr );
        }

        auto *node = godot::Object::cast_to<godot::Node>( ary_node[i] );
        if ( node != nullptr ) {
            _recurisive_dispose_node( node, node_release );
            if ( node->get_parent() != nullptr ) {
                node->get_parent()->remove_child( node );
            }
            if ( node_release ) {
                node->queue_free();
            }
        }
    }
}
