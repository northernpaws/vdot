// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_USER_MODEL_H
#define VDOT_CUBISM_USER_MODEL_H

#include <godot_cpp/classes/canvas_group.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>

#include <CubismFramework.hpp>
#include <Math/CubismVector2.hpp>
#include <Motion/ACubismMotion.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>

#include "cubism.h"

#include "cubism_effect.h"
#include "cubism_motion_entry.h"

class CubismModelProxy;
class CubismEffect;

struct anim_expression {
  public:
    godot::String expression_id;

  public:
    anim_expression() = default;
    explicit anim_expression( const Csm::csmChar *c_expression_id ) :
        expression_id( godot::String( c_expression_id ) ) {
    }

    [[nodiscard]] godot::String to_string() const {
        return godot::String( this->expression_id );
    }
};

class anim_motion {
  public:
    godot::String group;
    int32_t no = 0;

  public:
    anim_motion() = default;
    anim_motion( const Csm::csmChar *c_group, const int32_t c_no ) :
        group( godot::String( c_group ) ), no( c_no ) {
    }

    [[nodiscard]] godot::String to_string() const {
        godot::Array ary;
        ary.append( this->group );
        ary.append( this->no );

        return godot::String( "{0}_{1}" ).format( ary );
    }
};

class CubismModel : public godot::SubViewport {
    GDCLASS( CubismModel, SubViewport )

  public:
    CubismModel();
    ~CubismModel() override;

  public:
    enum moc3FileFormatVersion {
        CSM_MOC_VERSION_UNKNOWN = Live2D::Cubism::Core::csmMocVersion_Unknown,
        CSM_MOC_VERSION_30 = Live2D::Cubism::Core::csmMocVersion_30,
        CSM_MOC_VERSION_33 = Live2D::Cubism::Core::csmMocVersion_33,
        CSM_MOC_VERSION_40 = Live2D::Cubism::Core::csmMocVersion_40,
        CSM_MOC_VERSION_42 = Live2D::Cubism::Core::csmMocVersion_42,
        CSM_MOC_VERSION_50 = Live2D::Cubism::Core::csmMocVersion_50
    };

    enum Priority { PRIORITY_NONE = 0, PRIORITY_IDLE = 1, PRIORITY_NORMAL = 2, PRIORITY_FORCE = 3 };

    enum ParameterMode { FULL_PARAMETER = 0, NONE_PARAMETER = 1 };

    enum MotionProcessCallback { PHYSICS = 0, IDLE = 1, MANUAL = 2 };

    godot::String assets;
    CubismModelProxy *proxy_model;
    bool enable_load_expressions;
    bool enable_load_motions;

    float speed_scale;
    bool auto_scale;
    float adjust_scale;
    godot::Vector2 adjust_pos;
    godot::Vector2i mask_viewport_size;

    ParameterMode parameter_mode;
    MotionProcessCallback playback_process_mode;

    godot::Array ary_shader;
    godot::Array ary_parameter;
    godot::Array ary_part_opacity;

    Csm::csmBool anim_loop;
    Csm::csmBool anim_loop_fade_in;
    Csm::csmMap<godot::String, anim_expression> dict_anim_expression;
    godot::String curr_anim_expression_key;
    Csm::csmMap<godot::String, anim_motion> dict_anim_motion;
    godot::String curr_anim_motion_key;

    Csm::csmVector<CubismEffect *> _list_cubism_effect;
    bool cubism_effect_dirty;

  protected:
    static void _bind_methods();

  public:
    godot::Dictionary csm_get_version();
    moc3FileFormatVersion csm_get_latest_moc_version();
    moc3FileFormatVersion csm_get_moc_version();

    void set_assets( const godot::String assets );
    [[nodiscard]] godot::String get_assets() const;

    void set_load_expressions( const bool enable );
    [[nodiscard]] bool get_load_expressions() const;
    void set_load_motions( const bool enable );
    [[nodiscard]] bool get_load_motions() const;

    [[nodiscard]] godot::Dictionary get_canvas_info() const;

    [[nodiscard]] bool is_initialized() const;
    void clear();

    void set_parameter_mode( const ParameterMode value );
    [[nodiscard]] CubismModel::ParameterMode get_parameter_mode() const;

    void set_process_callback( const MotionProcessCallback value );
    [[nodiscard]] CubismModel::MotionProcessCallback get_process_callback() const;

    void set_speed_scale( const float speed );
    [[nodiscard]] float get_speed_scale() const;

    void set_auto_scale( const bool value );
    [[nodiscard]] bool get_auto_scale() const;

    void set_adjust_scale( const float scale ) {
        this->adjust_scale = scale;
    }
    [[nodiscard]] float get_adjust_scale() const {
        return this->adjust_scale;
    }

    void set_adjust_position( const godot::Vector2 pos ) {
        this->adjust_pos = pos;
    }
    godot::Vector2 get_adjust_position() const {
        return this->adjust_pos;
    }

    void set_mask_viewport_size( const godot::Vector2i size ) {
        this->mask_viewport_size = size;
    }
    godot::Vector2i get_mask_viewport_size() const {
        return this->mask_viewport_size;
    }

    [[nodiscard]] godot::Dictionary get_motions() const;
    godot::Ref<CubismMotionQueueEntryHandle> start_motion( const godot::String str_group,
                                                           const int32_t no,
                                                           const Priority priority );
    godot::Ref<CubismMotionQueueEntryHandle> start_motion_loop( const godot::String str_group,
                                                                const int32_t no,
                                                                const Priority priority,
                                                                const bool loop,
                                                                const bool loop_fade_in );
    [[nodiscard]] godot::Array get_cubism_motion_queue_entries() const;
    void stop_motion();

    [[nodiscard]] godot::Array get_expressions() const;
    void start_expression( const godot::String expression_id );
    void stop_expression();

    [[nodiscard]] godot::Array get_hit_areas() const;

    [[nodiscard]] godot::Array get_parameters() const;
    [[nodiscard]] godot::Array get_part_opacities() const;

    [[nodiscard]] godot::Dictionary get_meshes() const;

    void set_shader( const CubismShader e, const godot::Ref<godot::Shader> &shader ) {
        this->ary_shader[e] = shader;
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader( const CubismShader e ) const {
        return this->ary_shader[e];
    }

    // NormAdd
    void set_shader_add( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_NORM_ADD, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_add() const {
        return this->get_shader( CUBISM_SHADER_NORM_ADD );
    }

    // NormMix
    void set_shader_mix( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_NORM_MIX, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mix() const {
        return this->get_shader( CUBISM_SHADER_NORM_MIX );
    }

    // NormMul
    void set_shader_mul( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_NORM_MUL, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mul() const {
        return this->get_shader( CUBISM_SHADER_NORM_MUL );
    }

    // Mask
    void set_shader_mask( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask() const {
        return this->get_shader( CUBISM_SHADER_MASK );
    }

    // MaskAdd
    void set_shader_mask_add( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_ADD, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_add() const {
        return this->get_shader( CUBISM_SHADER_MASK_ADD );
    }
    void set_shader_mask_add_inv( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_ADD_INV, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_add_inv() const {
        return this->get_shader( CUBISM_SHADER_MASK_ADD_INV );
    }

    // MaskMix
    void set_shader_mask_mix( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_MIX, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_mix() const {
        return this->get_shader( CUBISM_SHADER_MASK_MIX );
    }
    void set_shader_mask_mix_inv( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_MIX_INV, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_mix_inv() const {
        return this->get_shader( CUBISM_SHADER_MASK_MIX_INV );
    }

    // MaskMul
    void set_shader_mask_mul( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_MUL, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_mul() const {
        return this->get_shader( CUBISM_SHADER_MASK_MUL );
    }
    void set_shader_mask_mul_inv( const godot::Ref<godot::Shader> &shader ) {
        this->set_shader( CUBISM_SHADER_MASK_MUL_INV, shader );
    }
    [[nodiscard]] godot::Ref<godot::Shader> get_shader_mask_mul_inv() const {
        return this->get_shader( CUBISM_SHADER_MASK_MUL_INV );
    }

    // for Signal
    static void on_motion_finished( Csm::ACubismMotion *motion );

    void _update( const float delta );

    void advance( const float delta );

    [[nodiscard]] bool check_cubism_effect_dirty() const;
    void cubism_effect_dirty_reset();

    // Properties
    void setup_property();

    bool _set( const godot::StringName &p_name, const godot::Variant &p_value );
    bool _get( const godot::StringName &p_name, godot::Variant &r_ret ) const;
    bool _property_can_revert( const godot::StringName &p_name ) const;
    bool _property_get_revert( const godot::StringName &p_name, godot::Variant &r_property ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *p_list );

    void _ready() override;
    void _enter_tree() override;
    void _exit_tree() override;
    void _process( double delta ) override;
    void _physics_process( double delta ) override;

    void _on_append_child_act( CubismEffect *node );
    void _on_remove_child_act( CubismEffect *node );
};

VARIANT_ENUM_CAST( CubismModel::moc3FileFormatVersion );
VARIANT_ENUM_CAST( CubismModel::Priority );
VARIANT_ENUM_CAST( CubismModel::ParameterMode );
VARIANT_ENUM_CAST( CubismModel::MotionProcessCallback );

#endif // VDOT_CUBISM_USER_MODEL_H
