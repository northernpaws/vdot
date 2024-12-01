// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/viewport_texture.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>

#include <CubismFramework.hpp>
#include <Model/CubismModel.hpp>
#include <Motion/CubismMotion.hpp>

#include "cubism_effect_eye_blink.h"
#include "cubism_motion_entry.h"
#include "cubism_value_parameter.h"
#include "cubism_value_part_opacity.h"
#include "renderer/cubism_model_proxy.h"

#include "cubism_model.h"

CubismModel::CubismModel() :
    proxy_model( nullptr ), enable_load_expressions( true ), enable_load_motions( true ),
    speed_scale( 1.0 ), auto_scale( true ), adjust_scale( 1.0 ), adjust_pos( 0.0, 0.0 ),
    mask_viewport_size( 0, 0 ), parameter_mode( ParameterMode::FULL_PARAMETER ),
    playback_process_mode( MotionProcessCallback::IDLE ), anim_loop( DEFAULT_PROP_ANIM_LOOP ),
    anim_loop_fade_in( DEFAULT_PROP_ANIM_LOOP_FADE_IN ), cubism_effect_dirty( false ) {

    this->ary_shader.resize( CUBISM_SHADER_MAX );
}

CubismModel::~CubismModel() {
    this->ary_shader.clear();
    this->clear();
}

void CubismModel::_bind_methods() {

    // csm
    godot::ClassDB::bind_method( godot::D_METHOD( "csm_get_version" ),
                                 &CubismModel::csm_get_version );
    godot::ClassDB::bind_method( godot::D_METHOD( "csm_get_latest_moc_version" ),
                                 &CubismModel::csm_get_latest_moc_version );
    godot::ClassDB::bind_method( godot::D_METHOD( "csm_get_moc_version" ),
                                 &CubismModel::csm_get_moc_version );

    // ModelData
    godot::ClassDB::bind_method( godot::D_METHOD( "set_assets", "assets" ),
                                 &CubismModel::set_assets );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_assets" ), &CubismModel::get_assets );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "assets", godot::PROPERTY_HINT_FILE,
                                       "*.model3.json" ),
                  "set_assets", "get_assets" );

    // Enable Load Expressions
    godot::ClassDB::bind_method( godot::D_METHOD( "set_load_expressions", "enable" ),
                                 &CubismModel::set_load_expressions );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_load_expressions" ),
                                 &CubismModel::get_load_expressions );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::BOOL, "load_expressions" ),
                  "set_load_expressions", "get_load_expressions" );

    // Enable Load Motions
    godot::ClassDB::bind_method( godot::D_METHOD( "set_load_motions", "enable" ),
                                 &CubismModel::set_load_motions );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_load_motions" ),
                                 &CubismModel::get_load_motions );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::BOOL, "load_motions" ), "set_load_motions",
                  "get_load_motions" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_canvas_info" ),
                                 &CubismModel::get_canvas_info );

    godot::ClassDB::bind_method( godot::D_METHOD( "clear" ), &CubismModel::clear );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_parameter_mode", "value" ),
                                 &CubismModel::set_parameter_mode );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameter_mode" ),
                                 &CubismModel::get_parameter_mode );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::INT, "parameter_mode",
                                       godot::PROPERTY_HINT_ENUM, "FullParameter,NoneParameter" ),
                  "set_parameter_mode", "get_parameter_mode" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_process_callback", "value" ),
                                 &CubismModel::set_process_callback );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_process_callback" ),
                                 &CubismModel::get_process_callback );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::INT, "playback_process_mode",
                                       godot::PROPERTY_HINT_ENUM, "Physics,Idle,Manual" ),
                  "set_process_callback", "get_process_callback" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_speed_scale", "value" ),
                                 &CubismModel::set_speed_scale );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_speed_scale" ),
                                 &CubismModel::get_speed_scale );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "speed_scale",
                                       godot::PROPERTY_HINT_RANGE, "0.0,256.0,0.1" ),
                  "set_speed_scale", "get_speed_scale" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_auto_scale", "value" ),
                                 &CubismModel::set_auto_scale );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_auto_scale" ),
                                 &CubismModel::get_auto_scale );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::BOOL, "auto_scale" ), "set_auto_scale",
                  "get_auto_scale" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_adjust_scale", "value" ),
                                 &CubismModel::set_adjust_scale );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_adjust_scale" ),
                                 &CubismModel::get_adjust_scale );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "adjust_scale",
                                       godot::PROPERTY_HINT_RANGE, "0.01,16.0,0.01" ),
                  "set_adjust_scale", "get_adjust_scale" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_adjust_position", "value" ),
                                 &CubismModel::set_adjust_position );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_adjust_position" ),
                                 &CubismModel::get_adjust_position );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2, "adjust_position" ),
                  "set_adjust_position", "get_adjust_position" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_mask_viewport_size", "value" ),
                                 &CubismModel::set_mask_viewport_size );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_mask_viewport_size" ),
                                 &CubismModel::get_mask_viewport_size );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2I, "mask_viewport_size" ),
                  "set_mask_viewport_size", "get_mask_viewport_size" );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_add" ),
                                 &CubismModel::set_shader_add );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_add" ),
                                 &CubismModel::get_shader_add );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mix" ),
                                 &CubismModel::set_shader_mix );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mix" ),
                                 &CubismModel::get_shader_mix );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mul" ),
                                 &CubismModel::set_shader_mul );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mul" ),
                                 &CubismModel::get_shader_mul );

    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask" ),
                                 &CubismModel::set_shader_mask );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask" ),
                                 &CubismModel::get_shader_mask );
    // MaskAdd
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_add" ),
                                 &CubismModel::set_shader_mask_add );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_add" ),
                                 &CubismModel::get_shader_mask_add );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_add_inv" ),
                                 &CubismModel::set_shader_mask_add_inv );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_add_inv" ),
                                 &CubismModel::get_shader_mask_add_inv );
    // MaskMix
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_mix" ),
                                 &CubismModel::set_shader_mask_mix );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_mix" ),
                                 &CubismModel::get_shader_mask_mix );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_mix_inv" ),
                                 &CubismModel::set_shader_mask_mix_inv );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_mix_inv" ),
                                 &CubismModel::get_shader_mask_mix_inv );
    // MaskMul
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_mul" ),
                                 &CubismModel::set_shader_mask_mul );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_mul" ),
                                 &CubismModel::get_shader_mask_mul );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_shader_mask_mul_inv" ),
                                 &CubismModel::set_shader_mask_mul_inv );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_shader_mask_mul_inv" ),
                                 &CubismModel::get_shader_mask_mul_inv );

    ADD_GROUP( "Shader", "" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_add",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_add", "get_shader_add" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mix",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mix", "get_shader_mix" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mul",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mul", "get_shader_mul" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask", "get_shader_mask" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_add",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_add", "get_shader_mask_add" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_add_inv",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_add_inv", "get_shader_mask_add_inv" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_mix",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_mix", "get_shader_mask_mix" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_mix_inv",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_mix_inv", "get_shader_mask_mix_inv" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_mul",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_mul", "get_shader_mask_mul" );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::OBJECT, "shader_mask_mul_inv",
                                       godot::PROPERTY_HINT_RESOURCE_TYPE, "Shader" ),
                  "set_shader_mask_mul_inv", "get_shader_mask_mul_inv" );

    // CubismMotion
    godot::ClassDB::bind_method( godot::D_METHOD( "get_motions" ), &CubismModel::get_motions );
    godot::ClassDB::bind_method( godot::D_METHOD( "start_motion", "group", "no", "priority" ),
                                 &CubismModel::start_motion );
    godot::ClassDB::bind_method(
        godot::D_METHOD( "start_motion_loop", "group", "no", "priority", "loop", "loop_fade_in" ),
        &CubismModel::start_motion_loop );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_cubism_motion_queue_entries" ),
                                 &CubismModel::get_cubism_motion_queue_entries );
    godot::ClassDB::bind_method( godot::D_METHOD( "stop_motion" ), &CubismModel::stop_motion );

    // CubismExpression
    godot::ClassDB::bind_method( godot::D_METHOD( "get_expressions" ),
                                 &CubismModel::get_expressions );
    godot::ClassDB::bind_method( godot::D_METHOD( "start_expression", "expression_id" ),
                                 &CubismModel::start_expression );
    godot::ClassDB::bind_method( godot::D_METHOD( "stop_expression" ),
                                 &CubismModel::stop_expression );

    // HitArea
    godot::ClassDB::bind_method( godot::D_METHOD( "get_hit_areas" ), &CubismModel::get_hit_areas );

    // Parameter
    godot::ClassDB::bind_method( godot::D_METHOD( "get_parameters" ),
                                 &CubismModel::get_parameters );

    // PartOpacity
    godot::ClassDB::bind_method( godot::D_METHOD( "get_part_opacities" ),
                                 &CubismModel::get_part_opacities );

    // Meshs
    godot::ClassDB::bind_method( godot::D_METHOD( "get_meshes" ), &CubismModel::get_meshes );

    godot::ClassDB::bind_method( godot::D_METHOD( "advance", "delta" ), &CubismModel::advance );

    ADD_SIGNAL( godot::MethodInfo( "motion_event",
                                   godot::PropertyInfo( godot::Variant::STRING, "value" ) ) );
#ifdef CUBISM_MOTION_CUSTOMDATA
    ADD_SIGNAL( godot::MethodInfo( SIGNAL_MOTION_FINISHED ) );
#endif // #ifdef CUBISM_MOTION_CUSTOMDATA

    // moc3FileFormatVersion
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_UNKNOWN );
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_30 );
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_33 );
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_40 );
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_42 );
    BIND_ENUM_CONSTANT( CSM_MOC_VERSION_50 );

    // Priority
    BIND_ENUM_CONSTANT( PRIORITY_NONE );
    BIND_ENUM_CONSTANT( PRIORITY_IDLE );
    BIND_ENUM_CONSTANT( PRIORITY_NORMAL );
    BIND_ENUM_CONSTANT( PRIORITY_FORCE );

    // ParameterMode
    BIND_ENUM_CONSTANT( FULL_PARAMETER );
    BIND_ENUM_CONSTANT( NONE_PARAMETER );

    // MotionProcessCallback
    BIND_ENUM_CONSTANT( PHYSICS );
    BIND_ENUM_CONSTANT( IDLE );
    BIND_ENUM_CONSTANT( MANUAL );
}

godot::Dictionary CubismModel::csm_get_version() {
    godot::Dictionary dict_version;
    const Live2D::Cubism::Core::csmVersion version = Live2D::Cubism::Core::csmGetVersion();

    dict_version["version"] = version;
    dict_version["major"] = ( version >> 24 ) & 0xFF;
    dict_version["minor"] = ( version >> 16 ) & 0xFF;
    dict_version["patch"] = version & 0xFFFF;

    return dict_version;
}

CubismModel::moc3FileFormatVersion CubismModel::csm_get_latest_moc_version() {
    return static_cast<moc3FileFormatVersion>( Live2D::Cubism::Core::csmGetLatestMocVersion() );
}

CubismModel::moc3FileFormatVersion CubismModel::csm_get_moc_version() {
    ERR_FAIL_COND_V( this->is_initialized() == false,
                     moc3FileFormatVersion::CSM_MOC_VERSION_UNKNOWN );
    return this->proxy_model->_moc3_file_format_version;
}

void CubismModel::set_assets( const godot::String p_assets ) {
    this->assets = p_assets;

    godot::Ref<godot::FileAccess> f = godot::FileAccess::open( p_assets, godot::FileAccess::READ );
    if ( f.is_null() ) {
        this->clear();
        return;
    }

    this->clear();
    this->proxy_model = CSM_NEW CubismModelProxy( this, this );

    if ( !this->proxy_model->model_load( p_assets ) ) {
        this->clear();
        return;
    }
    if ( !this->proxy_model->IsInitialized() ) {
        this->clear();
        return;
    }

    {
        Csm::CubismModel *model = this->proxy_model->GetModel();

        this->ary_parameter.clear();

        for ( Csm::csmInt32 index = 0; index < model->GetParameterCount(); index++ ) {
            godot::Ref<CubismParameter> param;
            param.instantiate();
            param->setup( model, index );
            this->ary_parameter.append( param );
        }
    }

    {
        Csm::CubismModel *model = this->proxy_model->GetModel();

        this->ary_part_opacity.clear();

        for ( Csm::csmInt32 index = 0; index < model->GetPartCount(); index++ ) {
            godot::Ref<CubismPartOpacity> param;
            param.instantiate();
            param->setup( model, index );
            this->ary_part_opacity.append( param );
        }
    }

    this->setup_property();
    this->notify_property_list_changed();
}

godot::String CubismModel::get_assets() const {
    return this->assets;
}

void CubismModel::set_load_expressions( const bool enable ) {
    this->enable_load_expressions = enable;
}
bool CubismModel::get_load_expressions() const {
    return this->enable_load_expressions;
}
void CubismModel::set_load_motions( const bool enable ) {
    this->enable_load_motions = enable;
}
bool CubismModel::get_load_motions() const {
    return this->enable_load_motions;
}

godot::Dictionary CubismModel::get_canvas_info() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Dictionary() );

    godot::Dictionary result;
    Live2D::Cubism::Core::csmVector2 vct_pixel_size;
    Live2D::Cubism::Core::csmVector2 vct_pixel_origin;
    Csm::csmFloat32 pixel_per_unit;

    Live2D::Cubism::Core::csmReadCanvasInfo( this->proxy_model->GetModel()->GetModel(),
                                             &vct_pixel_size, &vct_pixel_origin, &pixel_per_unit );

    result["size_in_pixels"] = godot::Vector2( vct_pixel_size.X, vct_pixel_size.Y );
    result["origin_in_pixels"] = godot::Vector2( vct_pixel_origin.X, vct_pixel_origin.Y );
    result["pixels_per_unit"] = pixel_per_unit;

    return result;
}

bool CubismModel::is_initialized() const {
    if ( this->proxy_model == nullptr ) {
        return false;
    }
    return this->proxy_model->IsInitialized();
}

void CubismModel::clear() {
    if ( this->proxy_model != nullptr ) {
        this->proxy_model->clear();
        CSM_DELETE( this->proxy_model );
        this->proxy_model = nullptr;
    }

    this->setup_property();
    this->notify_property_list_changed();
}

void CubismModel::set_parameter_mode( const ParameterMode value ) {
    this->parameter_mode = value;
}

CubismModel::ParameterMode CubismModel::get_parameter_mode() const {
    return this->parameter_mode;
}

void CubismModel::set_process_callback( const MotionProcessCallback value ) {
    this->playback_process_mode = value;
}

CubismModel::MotionProcessCallback CubismModel::get_process_callback() const {
    return this->playback_process_mode;
}

void CubismModel::set_speed_scale( const float speed ) {
    this->speed_scale = godot::CLAMP<float, float, float>( speed, 0.0, 256.0 );
}

float CubismModel::get_speed_scale() const {
    return this->speed_scale;
}

void CubismModel::set_auto_scale( const bool value ) {
    this->auto_scale = value;
}

bool CubismModel::get_auto_scale() const {
    return this->auto_scale;
}

godot::Dictionary CubismModel::get_motions() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Dictionary() );
    if ( !this->enable_load_motions ) {
        return {};
    }

    Csm::ICubismModelSetting *setting = this->proxy_model->_model_setting;

    godot::Dictionary dict_motion;

    for ( Csm::csmInt32 i = 0; i < setting->GetMotionGroupCount(); i++ ) {
        const Csm::csmChar *group = setting->GetMotionGroupName( i );
        godot::String gd_group;
        gd_group.parse_utf8( group );
        dict_motion[gd_group] = setting->GetMotionCount( group );
    }

    return dict_motion;
}

godot::Ref<CubismMotionQueueEntryHandle> CubismModel::start_motion( const godot::String str_group,
                                                                    const int32_t no,
                                                                    const Priority priority ) {
    return this->start_motion_loop( str_group, no, priority, false, true );
}

godot::Ref<CubismMotionQueueEntryHandle> CubismModel::start_motion_loop(
    const godot::String str_group, const int32_t no, const Priority priority, const bool loop,
    const bool loop_fade_in ) {
    godot::Ref<CubismMotionQueueEntryHandle> queue_handle;
    queue_handle.instantiate();

    if ( !this->is_initialized() ) {
        return queue_handle;
    }

    queue_handle->_handle = this->proxy_model->motion_start( str_group.utf8().ptr(), no, priority,
                                                             loop, loop_fade_in, this );

    return queue_handle;
}

godot::Array CubismModel::get_cubism_motion_queue_entries() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Array() );

    godot::Array ary_motion_entry;

    Csm::csmVector<Csm::CubismMotionQueueEntry *> *entry_vector_ptr =
        this->proxy_model->_motionManager->GetCubismMotionQueueEntries();

    for ( Csm::csmVector<Csm::CubismMotionQueueEntry *>::iterator i = entry_vector_ptr->Begin();
          i != entry_vector_ptr->End(); i++ ) {
        godot::Ref<CubismMotionEntry> e;
        e.instantiate();
        e->_entry = *i;
        ary_motion_entry.append( e );
    }

    return ary_motion_entry;
}

void CubismModel::stop_motion() {
    if ( !this->is_initialized() ) {
        return;
    }

    this->proxy_model->motion_stop();
}

godot::Array CubismModel::get_expressions() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Array() );
    if ( !this->enable_load_expressions ) {
        return {};
    }

    Csm::ICubismModelSetting *setting = this->proxy_model->_model_setting;

    godot::Array ary_expression;

    for ( Csm::csmInt32 i = 0; i < setting->GetExpressionCount(); i++ ) {
        const Csm::csmChar *name = setting->GetExpressionName( i );
        godot::String gd_name;
        gd_name.parse_utf8( name );
        ary_expression.append( gd_name );
    }

    return ary_expression;
}

void CubismModel::start_expression( const godot::String str_expression_id ) {
    if ( !this->is_initialized() ) {
        return;
    }

    this->proxy_model->expression_set( str_expression_id.utf8().ptr() );
}

void CubismModel::stop_expression() {
    if ( !this->is_initialized() ) {
        return;
    }

    this->proxy_model->expression_stop();
}

godot::Array CubismModel::get_hit_areas() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Array() );

    Csm::ICubismModelSetting *setting = this->proxy_model->_model_setting;

    godot::Array ary_hit_area;

    for ( Csm::csmInt32 i = 0; i < setting->GetHitAreasCount(); i++ ) {
        godot::Dictionary dict_hit_area;
        godot::String id;
        id.parse_utf8( setting->GetHitAreaId( i )->GetString().GetRawString() );
        godot::String name;
        name.parse_utf8( setting->GetHitAreaName( i ) );

        dict_hit_area["id"] = id;
        dict_hit_area["name"] = name;
        ary_hit_area.append( dict_hit_area );
    }

    return ary_hit_area;
}

godot::Array CubismModel::get_parameters() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Array() );

    return this->ary_parameter;
}

godot::Array CubismModel::get_part_opacities() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Array() );

    return this->ary_part_opacity;
}

godot::Dictionary CubismModel::get_meshes() const {
    ERR_FAIL_COND_V( this->is_initialized() == false, godot::Dictionary() );

    return this->proxy_model->_renderer_resource.dict_mesh;
}

void CubismModel::on_motion_finished( Csm::ACubismMotion *motion ) {
#ifdef CUBISM_MOTION_CUSTOMDATA
    CubismModel *m = static_cast<CubismModel *>( motion->GetFinishedMotionCustomData() );
    if ( m != nullptr ) {
        m->emit_signal( SIGNAL_MOTION_FINISHED );
    }
#endif // CUBISM_MOTION_CUSTOMDATA
}

void CubismModel::_update( const float delta ) {

    this->proxy_model->pro_update( delta * this->speed_scale );

    this->proxy_model->efx_update( delta * this->speed_scale );

    for ( Csm::csmInt32 index = 0; index < this->ary_parameter.size(); index++ ) {
        godot::Ref<CubismParameter> param = this->ary_parameter[index];
        if ( !param.is_null() ) {
            if ( param->hold ) {
                param->set_raw_value();
                param->changed = true;
            } else {
                param->set_raw_value();
                param->get_raw_value();
            }
        }
    }

    for ( Csm::csmInt32 index = 0; index < this->ary_part_opacity.size(); index++ ) {
        godot::Ref<CubismPartOpacity> param = this->ary_part_opacity[index];
        if ( !param.is_null() ) {
            param->set_raw_value();
            param->get_raw_value();
        }
    }

    this->proxy_model->epi_update( delta * this->speed_scale );

// https://github.com/godotengine/godot/issues/90030
// https://github.com/godotengine/godot/issues/90017
#ifdef COUNTERMEASURES_90017_90030
    if ( get_window()->is_visible() == true ) {
        if ( get_window()->get_mode() != Window::Mode::MODE_MINIMIZED ) {
            this->internal_model->update_node();
        }
    }
#else
    this->proxy_model->update_node();
#endif // COUNTERMEASURES_90017_90030
}

void CubismModel::advance( const float delta ) {
    ERR_FAIL_COND( this->is_initialized() == false );
    if ( this->playback_process_mode != MANUAL ) {
        return;
    }

    this->_update( delta );
}

bool CubismModel::check_cubism_effect_dirty() const {
    return this->cubism_effect_dirty;
}

void CubismModel::cubism_effect_dirty_reset() {
    this->cubism_effect_dirty = false;
}

void CubismModel::setup_property() {
    this->dict_anim_expression.Clear();
    this->dict_anim_motion.Clear();

    if ( !this->is_initialized() ) {
        return;
    }
    Csm::ICubismModelSetting *setting = this->proxy_model->_model_setting;

    // Property - Expression
    if ( this->enable_load_expressions ) {
        for ( Csm::csmInt32 i = 0; i < setting->GetExpressionCount(); i++ ) {
            const Csm::csmChar *expression_id = setting->GetExpressionName( i );
            anim_expression anim_e( expression_id );

            this->dict_anim_expression[anim_e.to_string()] = anim_e;
        }
    }

    // Property - Motion
    if ( this->enable_load_motions ) {
        for ( Csm::csmInt32 i = 0; i < setting->GetMotionGroupCount(); i++ ) {
            const Csm::csmChar *group = setting->GetMotionGroupName( i );
            for ( Csm::csmInt32 no = 0; no < setting->GetMotionCount( group ); no++ ) {
                anim_motion anim_m( group, no );

                this->dict_anim_motion[anim_m.to_string()] = anim_m;
            }
        }
    }
}

bool CubismModel::_set( const godot::StringName &p_name, const godot::Variant &p_value ) {
    if ( !this->is_initialized() ) {
        return false;
    }
    Csm::CubismModel *model = this->proxy_model->GetModel();

    if ( p_name == godot::String( PROP_ANIM_EXPRESSION ) ) {
        this->curr_anim_expression_key = p_value;
        if ( this->dict_anim_expression.IsExist( this->curr_anim_expression_key ) ) {
            anim_expression anim_e = this->dict_anim_expression[this->curr_anim_expression_key];
            this->start_expression( anim_e.expression_id );
        }

        return true;
    }

    if ( p_name == godot::String( PROP_ANIM_MOTION ) ) {
        this->curr_anim_motion_key = p_value;
        if ( this->dict_anim_motion.IsExist( this->curr_anim_motion_key ) ) {
            anim_motion anim_m = this->dict_anim_motion[this->curr_anim_motion_key];
            this->start_motion_loop( anim_m.group, anim_m.no, Priority::PRIORITY_FORCE,
                                     this->anim_loop, this->anim_loop_fade_in );
        }

        return true;
    }

    if ( p_name == godot::String( PROP_ANIM_LOOP ) ) {
        this->anim_loop = p_value;
        return true;
    }
    if ( p_name == godot::String( PROP_ANIM_LOOP_FADE_IN ) ) {
        this->anim_loop_fade_in = p_value;
        return true;
    }

    for ( Csm::csmInt32 index = 0; index < model->GetParameterCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetParameterId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            model->SetParameterValue( index, p_value );
            return true;
        }
    }

    for ( Csm::csmInt32 index = 0; index < model->GetPartCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetPartId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            model->SetPartOpacity( index, p_value );
            return true;
        }
    }

    return false;
}

bool CubismModel::_get( const godot::StringName &p_name, godot::Variant &r_ret ) const {
    if ( !this->is_initialized() ) {
        return false;
    }
    Csm::CubismModel *model = this->proxy_model->GetModel();

    if ( p_name == godot::String( PROP_ANIM_EXPRESSION ) ) {
        r_ret = this->curr_anim_expression_key;
        return true;
    }

    if ( p_name == godot::String( PROP_ANIM_MOTION ) ) {
        r_ret = this->curr_anim_motion_key;
        return true;
    }

    if ( p_name == godot::String( PROP_ANIM_LOOP ) ) {
        r_ret = this->anim_loop;
        return true;
    }
    if ( p_name == godot::String( PROP_ANIM_LOOP_FADE_IN ) ) {
        r_ret = this->anim_loop_fade_in;
        return true;
    }

    for ( Csm::csmInt32 index = 0; index < model->GetParameterCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetParameterId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            r_ret = model->GetParameterValue( index );
            return true;
        }
    }

    for ( Csm::csmInt32 index = 0; index < model->GetPartCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetPartId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            r_ret = model->GetPartOpacity( index );
            return true;
        }
    }

    return false;
}

bool CubismModel::_property_can_revert( const godot::StringName &p_name ) const {
    if ( !this->is_initialized() ) {
        return false;
    }
    Csm::CubismModel *model = this->proxy_model->GetModel();

    if ( p_name == godot::String( PROP_ANIM_LOOP ) ) {
        return true;
    }
    if ( p_name == godot::String( PROP_ANIM_LOOP_FADE_IN ) ) {
        return true;
    }

    for ( Csm::csmInt32 index = 0; index < model->GetParameterCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetParameterId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            return true;
        }
    }

    return false;
}

bool CubismModel::_property_get_revert( const godot::StringName &p_name,
                                        godot::Variant &r_property ) const {
    if ( !this->is_initialized() ) {
        return false;
    }
    Csm::CubismModel *model = this->proxy_model->GetModel();

    if ( p_name == godot::String( PROP_ANIM_LOOP ) ) {
        r_property = DEFAULT_PROP_ANIM_LOOP;
        return true;
    }
    if ( p_name == godot::String( PROP_ANIM_LOOP_FADE_IN ) ) {
        r_property = DEFAULT_PROP_ANIM_LOOP_FADE_IN;
        return true;
    }

    for ( Csm::csmInt32 index = 0; index < model->GetParameterCount(); index++ ) {
        godot::String name;
        name.parse_utf8( model->GetParameterId( index )->GetString().GetRawString() );

        if ( p_name == name ) {
            r_property = model->GetParameterDefaultValue( index );
            return true;
        }
    }

    return false;
}

void CubismModel::_get_property_list( godot::List<godot::PropertyInfo> *p_list ) {
    if ( !this->is_initialized() ) {
        return;
    }
    Csm::ICubismModelSetting *setting = this->proxy_model->_model_setting;
    godot::PackedStringArray ary_enum;

    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, PROP_ANIM_GROUP,
                                            godot::PROPERTY_HINT_NONE, "",
                                            godot::PROPERTY_USAGE_GROUP ) );

    p_list->push_back( godot::PropertyInfo( godot::Variant::BOOL, PROP_ANIM_LOOP ) );
    p_list->push_back( godot::PropertyInfo( godot::Variant::BOOL, PROP_ANIM_LOOP_FADE_IN ) );

    // Property - Expression
    ary_enum.clear();
    if ( this->enable_load_expressions ) {
        for ( Csm::csmInt32 i = 0; i < setting->GetExpressionCount(); i++ ) {
            const Csm::csmChar *expression_id = setting->GetExpressionName( i );
            anim_expression anim_e( expression_id );

            ary_enum.append( anim_e.to_string() );
        }
    }

    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, PROP_ANIM_EXPRESSION,
                                            godot::PROPERTY_HINT_ENUM,
                                            godot::String( "," ).join( ary_enum ) ) );

    // Property - Motion
    ary_enum.clear();
    if ( this->enable_load_motions ) {
        for ( Csm::csmInt32 i = 0; i < setting->GetMotionGroupCount(); i++ ) {
            const Csm::csmChar *group = setting->GetMotionGroupName( i );
            for ( Csm::csmInt32 no = 0; no < setting->GetMotionCount( group ); no++ ) {
                anim_motion anim_m( group, no );

                ary_enum.append( anim_m.to_string() );
            }
        }
    }

    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, PROP_ANIM_MOTION,
                                            godot::PROPERTY_HINT_ENUM,
                                            godot::String( "," ).join( ary_enum ) ) );

    // Property - Parameter
    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, PROP_PARAMETER_GROUP,
                                            godot::PROPERTY_HINT_NONE, "",
                                            godot::PROPERTY_USAGE_GROUP ) );

    for ( Csm::csmInt32 index = 0; index < this->ary_parameter.size(); index++ ) {
        godot::Ref<CubismParameter> param = this->ary_parameter[index];

        godot::Array ary_value;
        ary_value.append( param->minimum_value );
        ary_value.append( param->maximum_value );

        godot::PropertyInfo pinfo( godot::Variant::FLOAT, param->id, godot::PROPERTY_HINT_RANGE,
                                   godot::String( "{0},{1}" ).format( ary_value ),
                                   godot::PROPERTY_USAGE_DEFAULT );

        p_list->push_back( pinfo );
    }

    // Property - PartOpacity
    p_list->push_back( godot::PropertyInfo( godot::Variant::STRING, PROP_PART_OPACITY_GROUP,
                                            godot::PROPERTY_HINT_NONE, "",
                                            godot::PROPERTY_USAGE_GROUP ) );

    for ( Csm::csmInt32 index = 0; index < this->ary_part_opacity.size(); index++ ) {
        godot::Ref<CubismPartOpacity> param = this->ary_part_opacity[index];

        godot::Array ary_value;
        ary_value.append( 0.0 );
        ary_value.append( 1.0 );

        godot::PropertyInfo pinfo( godot::Variant::FLOAT, param->id, godot::PROPERTY_HINT_RANGE,
                                   godot::String( "{0},{1}" ).format( ary_value ),
                                   godot::PROPERTY_USAGE_DEFAULT );

        p_list->push_back( pinfo );
    }
}

void CubismModel::_ready() {
    // Setup SubViewport
    this->set_disable_3d( true ); // SUBVIEWPORT_DISABLE_3D_FLAG
    this->set_clear_mode( SubViewport::ClearMode::CLEAR_MODE_ALWAYS );
    // set_update_mode must be specified
    this->set_update_mode( SubViewport::UpdateMode::UPDATE_ALWAYS );
    this->set_disable_input( true );
    // Memory leak when set_use_own_world_3d is true
    // https://github.com/godotengine/godot/issues/81476
    this->set_use_own_world_3d( false ); // SUBVIEWPORT_USE_OWN_WORLD_3D_FLAG
    // Memory leak when set_transparent_background is true(* every time & window minimize)
    // https://github.com/godotengine/godot/issues/89651
    this->set_transparent_background( true );
}

void CubismModel::_enter_tree() {
    if ( !this->is_initialized() ) {
        return;
    }
}

void CubismModel::_exit_tree() {
    if ( !this->is_initialized() ) {
        return;
    }
}

void CubismModel::_process( double delta ) {
    if ( !this->is_initialized() ) {
        return;
    }
    if ( this->playback_process_mode != IDLE ) {
        return;
    }

    this->_update( static_cast<float>(delta) );
}

void CubismModel::_physics_process( double delta ) {
    if ( !this->is_initialized() ) {
        return;
    }
    if ( this->playback_process_mode != PHYSICS ) {
        return;
    }

    this->_update( static_cast<float>(delta) );
}

void CubismModel::_on_append_child_act( CubismEffect *node ) {
    this->_list_cubism_effect.PushBack( node );
    this->cubism_effect_dirty = true;
}

void CubismModel::_on_remove_child_act( CubismEffect *node ) {
    for ( Csm::csmVector<CubismEffect *>::iterator i = this->_list_cubism_effect.Begin();
          i != this->_list_cubism_effect.End(); i++ ) {
        if ( *i == node ) {
            this->_list_cubism_effect.Erase( i );
            break;
        }
    }
    this->cubism_effect_dirty = true;
}
