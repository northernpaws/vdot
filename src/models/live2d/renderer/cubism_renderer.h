// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_RENDERER_H
#define VDOT_CUBISM_RENDERER_H

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include "../cubism.h"

#include "../cubism_effect.h"

class CubismModel;

class CubismRenderer {
  public:
    CubismRenderer( CubismModel *owner_viewport, godot::Node *parent_node );
    ~CubismRenderer();

    void clear();

    godot::SubViewport *request_viewport();
    godot::MeshInstance2D *request_mesh_instance();

    void pro_proc( const Csm::csmInt32 viewport_count, const Csm::csmInt32 mesh_instance_count );
    void epi_proc();

    void dispose_node( const bool node_release );

    // Shader
    godot::Ref<godot::Shader> get_shader( const CubismShader e ) const {
        return this->ary_shader[e];
    }

  public:
    const CubismModel *_owner_viewport;
    godot::Node *_parent_node;

    godot::Array ary_texture;
    godot::Array ary_shader;
    godot::Dictionary dict_mesh;
    Csm::csmInt32 sub_viewport_counter;
    godot::TypedArray<godot::SubViewport> ary_sub_viewport;
    Csm::csmInt32 mesh_instance_counter;
    godot::TypedArray<godot::MeshInstance2D> ary_mesh_instance;

    // Adjust Parameters
    godot::Vector2 adjust_pos;
    float adjust_scale;

    // Render parameters
    godot::Vector2i vct_canvas_size;
    godot::Vector2i vct_mask_size;
    float RATIO;
    float CALCULATED_PPUNIT_C;
    float CALCULATED_PPUNIT_M;
    godot::Vector2 CALCULATED_ORIGIN_C;
    godot::Vector2 CALCULATED_ORIGIN_M;
};

#endif // VDOT_CUBISM_RENDERER_H
