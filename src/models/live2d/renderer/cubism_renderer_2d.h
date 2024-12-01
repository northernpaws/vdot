// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_RENDERER_2D_H
#define VDOT_CUBISM_RENDERER_2D_H

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include <Rendering/CubismRenderer.hpp>

#include "../cubism.h"

#include "../cubism_model.h"

#include "cubism_renderer.h"

class CubismRenderer2D : public Live2D::Cubism::Framework::Rendering::CubismRenderer {
    friend class ::CubismRenderer;

  public:
    CubismRenderer2D();
    virtual ~CubismRenderer2D();

  private:
    godot::Ref<godot::ShaderMaterial> make_ShaderMaterial( const Csm::CubismModel *model,
                                                           const Csm::csmInt32 index,
                                                           const ::CubismRenderer &res ) const;
    void make_ArrayMesh_prepare( const Csm::CubismModel *model, ::CubismRenderer &res );

    godot::Ref<godot::ArrayMesh> make_ArrayMesh( const Csm::CubismModel *model,
                                                 const Csm::csmInt32 index, const bool makemask,
                                                 const ::CubismRenderer &res ) const;

    void update_mask( godot::SubViewport *viewport, const Csm::csmInt32 index,
                      ::CubismRenderer &res );

  public:
    Csm::csmInt32 calc_viewport_count() const;
    Csm::csmInt32 calc_mesh_instance_count() const;
    godot::Vector2 get_size( const Csm::CubismModel *model ) const;
    godot::Vector2 get_origin( const Csm::CubismModel *model ) const;
    float get_ppunit( const Csm::CubismModel *model ) const;

    void update( ::CubismRenderer &res );
    void update( ::CubismRenderer &res, const bool update_node, const bool update_mesh );

    virtual void Initialize( Csm::CubismModel *model, Csm::csmInt32 maskBufferCount );
    void DoDrawModel();
    void SaveProfile();
    void RestoreProfile();
};

#endif // VDOT_CUBISM_RENDERER_2D_H
