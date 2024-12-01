// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#include "../cubism.h"

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "cubism_renderer_2d.h"

#include "cubism_model_proxy.h"

CubismModelProxy::CubismModelProxy( CubismModel *owner_viewport, godot::Node *parent_node ) :
    CubismUserModel(), _owner_viewport( owner_viewport ), _parent_node( parent_node ),
    _renderer_resource( owner_viewport, parent_node ),
    _moc3_file_format_version( CubismModel::moc3FileFormatVersion::CSM_MOC_VERSION_UNKNOWN ),
    _model_pathname( "" ), _model_setting( nullptr ) {

    _debugMode = false;
}

CubismModelProxy::~CubismModelProxy() {
    this->clear();
}

bool CubismModelProxy::model_load( const godot::String &model_pathname ) {
    this->_model_pathname = model_pathname;
    this->_updating = true;
    this->_initialized = false;
    this->_model_setting = nullptr;

    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( this->_model_pathname );
    if ( buffer.size() == 0 ) {
        return false;
    }

    this->clear();

    this->_model_setting = CSM_NEW Live2D::Cubism::Framework::CubismModelSettingJson(
        buffer.ptr(), static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );

    // setup Live2D model
    if ( strcmp( this->_model_setting->GetModelFileName(), "" ) == 0 ) {
        return false;
    } else {
        godot::String gd_filename;
        gd_filename.parse_utf8( this->_model_setting->GetModelFileName() );
        godot::String moc3_pathname = this->_model_pathname.get_base_dir().path_join( gd_filename );

        buffer = godot::FileAccess::get_file_as_bytes( moc3_pathname );
        this->LoadModel( buffer.ptr(),
                         static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );

        const Live2D::Cubism::Core::csmVersion version = Live2D::Cubism::Core::csmGetMocVersion(
            buffer.ptr(), static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );
        this->_moc3_file_format_version =
            static_cast<CubismModel::moc3FileFormatVersion>( version );
    }

    // Expression
    if ( this->_owner_viewport->enable_load_expressions ) {
        this->expression_load();
    }

    // Physics
    this->physics_load();
    // Pose
    this->pose_load();
    // UserData
    this->userdata_load();

    // EyeBlink(Parameters)
    {
        Csm::csmInt32 param_count = this->_model_setting->GetEyeBlinkParameterCount();
        for ( Csm::csmInt32 i = 0; i < param_count; ++i ) {
            this->_list_eye_blink.PushBack( this->_model_setting->GetEyeBlinkParameterId( i ) );
        }
    }

    // LipSync(Parameters)
    {
        Csm::csmInt32 param_count = this->_model_setting->GetLipSyncParameterCount();
        for ( Csm::csmInt32 i = 0; i < param_count; ++i ) {
            this->_list_lipsync.PushBack( this->_model_setting->GetLipSyncParameterId( i ) );
        }
    }

    if ( this->_model_setting == nullptr || this->_modelMatrix == nullptr ) {
        this->clear();
        return false;
    }

    this->_model->SaveParameters();

    // Motion
    if ( this->_owner_viewport->enable_load_motions ) {
        this->motion_load();
    }

    // GDCubismEffect
    this->effect_init();

    this->CreateRenderer();

    // Resource(Texture)
    this->model_load_resource();

    this->stop();

    this->_updating = false;
    this->_initialized = true;

    // ------------------------------------------------------------------------
    // The process to make the mesh available immediately after initialization.
    // The process is almost the same as the CubismModelProxy::update_node() function.
    {
        auto *renderer = this->GetRenderer<CubismRenderer2D>();

        // Update Adjust Parameter(s)
        this->_renderer_resource.adjust_scale = this->_owner_viewport->adjust_scale;
        this->_renderer_resource.adjust_pos = this->_owner_viewport->adjust_pos;

        this->_renderer_resource.pro_proc( renderer->calc_viewport_count(),
                                           renderer->calc_mesh_instance_count() );

        renderer->IsPremultipliedAlpha( false );
        renderer->DrawModel();
        renderer->update( this->_renderer_resource, false, true );

        this->_renderer_resource.epi_proc();
    }
    // ------------------------------------------------------------------------

    return true;
}

void CubismModelProxy::model_load_resource() {
    godot::ResourceLoader *res_loader = memnew( godot::ResourceLoader );

    this->_renderer_resource.ary_texture.clear();

    for ( Live2D::Cubism::Framework::csmInt32 index = 0;
          index < this->_model_setting->GetTextureCount(); index++ ) {
        if ( strcmp( this->_model_setting->GetTextureFileName( index ), "" ) == 0 ) {
            continue;
        }

        godot::String gd_filename;
        gd_filename.parse_utf8( this->_model_setting->GetTextureFileName( index ) );
        godot::String texture_pathname =
            this->_model_pathname.get_base_dir().path_join( gd_filename );

        godot::Ref<godot::Texture2D> tex = res_loader->load( texture_pathname );

        this->_renderer_resource.ary_texture.append( tex );
    }

    memdelete( res_loader );
}

void CubismModelProxy::pro_update( const float delta ) {
    if ( !this->IsInitialized() ) {
        return;
    }
    if ( this->_model_setting == nullptr ) {
        return;
    }
    if ( this->_model == nullptr ) {
        return;
    }

    this->effect_batch( delta, EFFECT_CALL_PROLOGUE );

    if ( this->_owner_viewport->parameter_mode == CubismModel::ParameterMode::FULL_PARAMETER ) {
        this->_model->LoadParameters();
        this->_motionManager->UpdateMotion( this->_model, delta );
        this->_model->SaveParameters();
    }

    if ( this->_expressionManager != nullptr ) {
        this->_expressionManager->UpdateMotion( this->_model, delta );
    }

    this->_model->GetModelOpacity();
}

void CubismModelProxy::efx_update( const float delta ) {
    if ( !this->IsInitialized() ) {
        return;
    }
    if ( this->_model_setting == nullptr ) {
        return;
    }
    if ( this->_model == nullptr ) {
        return;
    }

    if ( this->_owner_viewport->check_cubism_effect_dirty() ) {
        this->effect_term();
        this->effect_init();
        this->_owner_viewport->cubism_effect_dirty_reset();
    }

    this->effect_batch( delta, EFFECT_CALL_PROCESS );
}

void CubismModelProxy::epi_update( const float delta ) {
    if ( !this->IsInitialized() ) {
        return;
    }
    if ( this->_model_setting == nullptr ) {
        return;
    }
    if ( this->_model == nullptr ) {
        return;
    }

    if ( this->_physics != nullptr ) {
        this->_physics->Evaluate( this->_model, delta );
    }
    if ( this->_pose != nullptr ) {
        this->_pose->UpdateParameters( this->_model, delta );
    }

    this->_model->Update();
    this->effect_batch( delta, EFFECT_CALL_EPILOGUE );
}

void CubismModelProxy::update_node() {
    if ( !this->IsInitialized() ) {
        return;
    }

    auto *renderer = this->GetRenderer<CubismRenderer2D>();

    // Update Adjust Parameter(s)
    this->_renderer_resource.adjust_scale = this->_owner_viewport->adjust_scale;
    this->_renderer_resource.adjust_pos = this->_owner_viewport->adjust_pos;

    this->_renderer_resource.pro_proc( renderer->calc_viewport_count(),
                                       renderer->calc_mesh_instance_count() );

    renderer->IsPremultipliedAlpha( false );
    renderer->DrawModel();
    renderer->update( this->_renderer_resource );

    this->_renderer_resource.epi_proc();
}

void CubismModelProxy::clear() {

    this->DeleteRenderer();

    this->_renderer_resource.clear();

    {
        this->expression_stop();
        for ( Live2D::Cubism::Framework::csmMap<
                  Live2D::Cubism::Framework::csmString,
                  Live2D::Cubism::Framework::CubismExpressionMotion *>::const_iterator i =
                  this->_map_expression.Begin();
              i != this->_map_expression.End(); i++ ) {
            Live2D::Cubism::Framework::ACubismMotion::Delete( i->Second );
        }
        this->_map_expression.Clear();
    }

    {
        this->motion_stop();
        for ( Live2D::Cubism::Framework::csmMap<
                  Live2D::Cubism::Framework::csmString,
                  Live2D::Cubism::Framework::CubismMotion *>::const_iterator i =
                  this->_map_motion.Begin();
              i != this->_map_motion.End(); i++ ) {
            Live2D::Cubism::Framework::ACubismMotion::Delete( i->Second );
        }
        this->_map_motion.Clear();
    }

    this->effect_term();

    this->_list_eye_blink.Clear();
    this->_list_lipsync.Clear();

    if ( this->_model_setting != nullptr ) {
        this->_initialized = false;

        CSM_DELETE( this->_model_setting );
        this->_model_setting = nullptr;
    }
}

void CubismModelProxy::stop() {
    this->expression_stop();
    this->motion_stop();
}

void CubismModelProxy::expression_set( const char *expression_id ) {
    Live2D::Cubism::Framework::ACubismMotion *motion =
        this->_map_expression[Live2D::Cubism::Framework::csmString( expression_id )];

    if ( motion != nullptr ) {
        this->_expressionManager->StartMotionPriority( motion, false,
                                                       CubismModel::Priority::PRIORITY_FORCE );
    }
}

void CubismModelProxy::expression_stop() {
    if ( this->_expressionManager == nullptr ) {
        return;
    }
    this->_expressionManager->StopAllMotions();
}

Live2D::Cubism::Framework::CubismMotionQueueEntryHandle CubismModelProxy::motion_start(
    const char *group, const int32_t no, const int32_t priority, const bool loop,
    const bool loop_fade_in, void *custom_data ) {

    if ( priority == CubismModel::Priority::PRIORITY_FORCE ) {
        this->_motionManager->SetReservePriority( priority );
    } else if ( !this->_motionManager->ReserveMotion( priority ) ) {
        return Live2D::Cubism::Framework::InvalidMotionQueueEntryHandleValue;
    }

    Live2D::Cubism::Framework::csmString name =
        Live2D::Cubism::Framework::Utils::CubismString::GetFormatedString( "%s_%d", group, no );

    Live2D::Cubism::Framework::CubismMotion *motion = this->_map_motion[name];

    if ( motion == nullptr ) {
        return Live2D::Cubism::Framework::InvalidMotionQueueEntryHandleValue;
    }

    motion->IsLoop( loop );
    motion->IsLoopFadeIn( loop_fade_in );
    motion->SetFinishedMotionHandler( CubismModel::on_motion_finished );
#ifdef CUBISM_MOTION_CUSTOMDATA
    motion->SetFinishedMotionCustomData( custom_data );
#endif // CUBISM_MOTION_CUSTOMDATA

    return this->_motionManager->StartMotionPriority( motion, false, priority );
}

void CubismModelProxy::motion_stop() {
    if ( this->_motionManager == nullptr ) {
        return;
    }
    this->_motionManager->StopAllMotions();
}

void CubismModelProxy::MotionEventFired( const Live2D::Cubism::Framework::csmString &eventValue ) {
    if ( this->_owner_viewport != nullptr ) {
        godot::String value;
        value.parse_utf8( eventValue.GetRawString() );
        this->_owner_viewport->emit_signal( "motion_event", value );
    }
}

void CubismModelProxy::expression_load() {
    if ( this->_model_setting == nullptr ) {
        return;
    }
    if ( this->_model_setting->GetExpressionCount() == 0 ) {
        return;
    }

    for ( Live2D::Cubism::Framework::csmInt32 i = 0; i < this->_model_setting->GetExpressionCount();
          i++ ) {
        Live2D::Cubism::Framework::csmString name = this->_model_setting->GetExpressionName( i );

        godot::String gd_filename;
        gd_filename.parse_utf8( this->_model_setting->GetExpressionFileName( i ) );
        godot::String expression_pathname =
            this->_model_pathname.get_base_dir().path_join( gd_filename );

        godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( expression_pathname );
        auto *motion =
            dynamic_cast<Live2D::Cubism::Framework::CubismExpressionMotion *>( this->LoadExpression(
                buffer.ptr(), static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ),
                this->_model_setting->GetExpressionName( i ) ) );

        if ( this->_map_expression[name] != nullptr ) {
            Live2D::Cubism::Framework::ACubismMotion::Delete( this->_map_expression[name] );
            this->_map_expression[name] = nullptr;
        }

        this->_map_expression[name] = motion;
    }
}

void CubismModelProxy::physics_load() {
    if ( strcmp( this->_model_setting->GetPhysicsFileName(), "" ) == 0 ) {
        return;
    }

    godot::String gd_filename;
    gd_filename.parse_utf8( this->_model_setting->GetPhysicsFileName() );
    godot::String physics_pathname = this->_model_pathname.get_base_dir().path_join( gd_filename );

    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( physics_pathname );
    if ( buffer.size() > 0 ) {
        this->LoadPhysics( buffer.ptr(),
                           static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );
    }
}

void CubismModelProxy::pose_load() {
    if ( strcmp( this->_model_setting->GetPoseFileName(), "" ) == 0 ) {
        return;
    }

    godot::String gd_filename;
    gd_filename.parse_utf8( this->_model_setting->GetPoseFileName() );
    godot::String pose_pathname = this->_model_pathname.get_base_dir().path_join( gd_filename );

    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( pose_pathname );
    if ( buffer.size() > 0 ) {
        this->LoadPose( buffer.ptr(),
                        static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );
    }
}

void CubismModelProxy::userdata_load() {
    if ( strcmp( this->_model_setting->GetUserDataFile(), "" ) == 0 ) {
        return;
    }

    godot::String gd_filename;
    gd_filename.parse_utf8( this->_model_setting->GetUserDataFile() );
    godot::String userdata_pathname = this->_model_pathname.get_base_dir().path_join( gd_filename );

    godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( userdata_pathname );
    if ( buffer.size() > 0 ) {
        this->LoadUserData( buffer.ptr(),
                            static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ) );
    }
}

void CubismModelProxy::motion_load() {
    if ( this->_model_setting == nullptr ) {
        return;
    }
    if ( this->_model_setting->GetMotionGroupCount() == 0 ) {
        return;
    }

    for ( Live2D::Cubism::Framework::csmInt32 ig = 0;
          ig < this->_model_setting->GetMotionGroupCount(); ig++ ) {
        // PreloadMotionGroup(group);
        const Live2D::Cubism::Framework::csmChar *group =
            this->_model_setting->GetMotionGroupName( ig );
        const Live2D::Cubism::Framework::csmInt32 motion_count =
            this->_model_setting->GetMotionCount( group );

        if ( motion_count == 0 ) {
            continue;
        }

        for ( Live2D::Cubism::Framework::csmInt32 im = 0; im < motion_count; im++ ) {
            Live2D::Cubism::Framework::csmString name =
                Live2D::Cubism::Framework::Utils::CubismString::GetFormatedString( "%s_%d", group,
                                                                                   im );

            godot::String gd_filename;
            gd_filename.parse_utf8( this->_model_setting->GetMotionFileName( group, im ) );
            godot::String motion_pathname =
                this->_model_pathname.get_base_dir().path_join( gd_filename );

            godot::PackedByteArray buffer = godot::FileAccess::get_file_as_bytes( motion_pathname );
            auto *motion =
                dynamic_cast<Live2D::Cubism::Framework::CubismMotion *>( this->LoadMotion(
                    buffer.ptr(),
                    static_cast<Live2D::Cubism::Framework::csmSizeInt>( buffer.size() ),
                    name.GetRawString() ) );

            Live2D::Cubism::Framework::csmFloat32 fade_time_sec =
                this->_model_setting->GetMotionFadeInTimeValue( group, im );
            if ( fade_time_sec >= 0.0f ) {
                motion->SetFadeInTime( fade_time_sec );
            }

            fade_time_sec = this->_model_setting->GetMotionFadeOutTimeValue( group, im );
            if ( fade_time_sec >= 0.0f ) {
                motion->SetFadeOutTime( fade_time_sec );
            }
            static_cast<Live2D::Cubism::Framework::CubismMotion *>( motion )->SetEffectIds(
                this->_list_eye_blink, this->_list_lipsync );

            if ( this->_map_motion[name] != nullptr ) {
                Live2D::Cubism::Framework::ACubismMotion::Delete( this->_map_motion[name] );
                this->_map_motion[name] = nullptr;
            }

            this->_map_motion[name] = motion;
        }
    }
}

void CubismModelProxy::effect_init() {
    for ( Csm::csmVector<CubismEffect *>::iterator i =
              this->_owner_viewport->_list_cubism_effect.Begin();
          i != this->_owner_viewport->_list_cubism_effect.End(); i++ ) {
        ( *i )->_cubism_init( this );
    }
}

void CubismModelProxy::effect_term() {
    for ( Csm::csmVector<CubismEffect *>::iterator i =
              this->_owner_viewport->_list_cubism_effect.Begin();
          i != this->_owner_viewport->_list_cubism_effect.End(); i++ ) {
        ( *i )->_cubism_term( this );
    }
}

void CubismModelProxy::effect_batch( const float delta, const EFFECT_CALL efx_call ) {
    for ( Csm::csmVector<CubismEffect *>::iterator i =
              this->_owner_viewport->_list_cubism_effect.Begin();
          i != this->_owner_viewport->_list_cubism_effect.End(); i++ ) {
        switch ( efx_call ) {
            case EFFECT_CALL_PROLOGUE:
                ( *i )->_cubism_prologue( this, delta );
                break;
            case EFFECT_CALL_PROCESS:
                ( *i )->_cubism_process( this, delta );
                break;
            case EFFECT_CALL_EPILOGUE:
                ( *i )->_cubism_epilogue( this, delta );
                break;
        }
    }
}
