// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_TARGET_POINT_H
#define VDOT_CUBISM_EFFECT_TARGET_POINT_H

#include "cubism.h"

#include "cubism_effect.h"
#include "renderer/cubism_model_proxy.h"

class CubismEffectTargetPoint : public CubismEffect {
    GDCLASS( CubismEffectTargetPoint, CubismEffect )

  private:
    enum E_PARAM {
        HEAD_ANGLE_X,
        HEAD_ANGLE_Y,
        HEAD_ANGLE_Z,
        BODY_ANGLE_X,
        EYES_BALL_X,
        EYES_BALL_Y
    };

  protected:
    static void _bind_methods() {

        godot::ClassDB::bind_method( godot::D_METHOD( "set_target", "target" ),
                                     &CubismEffectTargetPoint::set_target );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_target" ),
                                     &CubismEffectTargetPoint::get_target );

        ADD_GROUP( "Head", "" );
        godot::ClassDB::bind_method( godot::D_METHOD( "set_head_angle_x", "id" ),
                                     &CubismEffectTargetPoint::set_head_angle_x );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_head_angle_x" ),
                                     &CubismEffectTargetPoint::get_head_angle_x );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "head_angle_x" ),
                      "set_head_angle_x", "get_head_angle_x" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_head_angle_y", "id" ),
                                     &CubismEffectTargetPoint::set_head_angle_y );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_head_angle_y" ),
                                     &CubismEffectTargetPoint::get_head_angle_y );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "head_angle_y" ),
                      "set_head_angle_y", "get_head_angle_y" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_head_angle_z", "id" ),
                                     &CubismEffectTargetPoint::set_head_angle_z );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_head_angle_z" ),
                                     &CubismEffectTargetPoint::get_head_angle_z );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "head_angle_z" ),
                      "set_head_angle_z", "get_head_angle_z" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_head_range", "range" ),
                                     &CubismEffectTargetPoint::set_head_range );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_head_range" ),
                                     &CubismEffectTargetPoint::get_head_range );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "head_range" ), "set_head_range",
                      "get_head_range" );

        ADD_GROUP( "Body", "" );
        godot::ClassDB::bind_method( godot::D_METHOD( "set_body_angle_x", "id" ),
                                     &CubismEffectTargetPoint::set_body_angle_x );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_body_angle_x" ),
                                     &CubismEffectTargetPoint::get_body_angle_x );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "body_angle_x" ),
                      "set_body_angle_x", "get_body_angle_x" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_body_range", "range" ),
                                     &CubismEffectTargetPoint::set_body_range );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_body_range" ),
                                     &CubismEffectTargetPoint::get_body_range );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "body_range" ), "set_body_range",
                      "get_body_range" );

        ADD_GROUP( "Eyes", "" );
        godot::ClassDB::bind_method( godot::D_METHOD( "set_eyes_ball_x", "id" ),
                                     &CubismEffectTargetPoint::set_eyes_ball_x );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_eyes_ball_x" ),
                                     &CubismEffectTargetPoint::get_eyes_ball_x );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "eyes_ball_x" ),
                      "set_eyes_ball_x", "get_eyes_ball_x" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_eyes_ball_y", "id" ),
                                     &CubismEffectTargetPoint::set_eyes_ball_y );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_eyes_ball_y" ),
                                     &CubismEffectTargetPoint::get_eyes_ball_y );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "eyes_ball_y" ),
                      "set_eyes_ball_y", "get_eyes_ball_y" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_eyes_range", "range" ),
                                     &CubismEffectTargetPoint::set_eyes_range );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_eyes_range" ),
                                     &CubismEffectTargetPoint::get_eyes_range );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "eyes_range" ), "set_eyes_range",
                      "get_eyes_range" );
    }

  private:
    void set_head_angle_x( const godot::String id ) {
        this->head_angle_x = id;
        this->initialized = false;
    }
    godot::String get_head_angle_x() const {
        return this->head_angle_x;
    }
    void set_head_angle_y( const godot::String id ) {
        this->head_angle_y = id;
        this->initialized = false;
    }
    godot::String get_head_angle_y() const {
        return this->head_angle_y;
    }
    void set_head_angle_z( const godot::String id ) {
        this->head_angle_z = id;
        this->initialized = false;
    }
    godot::String get_head_angle_z() const {
        return this->head_angle_z;
    }

    void set_body_angle_x( const godot::String id ) {
        this->body_angle_x = id;
        this->initialized = false;
    }
    godot::String get_body_angle_x() const {
        return this->body_angle_x;
    }

    void set_eyes_ball_x( const godot::String id ) {
        this->eyes_ball_x = id;
        this->initialized = false;
    }
    godot::String get_eyes_ball_x() const {
        return this->eyes_ball_x;
    }
    void set_eyes_ball_y( const godot::String id ) {
        this->eyes_ball_y = id;
        this->initialized = false;
    }
    godot::String get_eyes_ball_y() const {
        return this->eyes_ball_y;
    }

  private:
    Csm::CubismTargetPoint *_target_point = nullptr;
    godot::String head_angle_x = "ParamAngleX";
    godot::String head_angle_y = "ParamAngleY";
    godot::String head_angle_z = "ParamAngleZ";
    godot::String body_angle_x = "ParamBodyAngleX";
    godot::String eyes_ball_x = "ParamEyeBallX";
    godot::String eyes_ball_y = "ParamEyeBallY";

    Csm::csmFloat32 _headRange = 30.0;
    Csm::csmFloat32 _bodyRange = 10.0;
    Csm::csmFloat32 _eyesRange = 1.0;

    Csm::csmMap<E_PARAM, Csm::csmInt32> _map_param_idx;
    bool initialized = false;

  private:
    Csm::csmInt32 find_idx( Csm::CubismModel *_model, const Csm::csmString name ) const {
        for ( Csm::csmInt32 index = 0; index < _model->GetParameterCount(); index++ ) {
            if ( _model->GetParameterId( index )->GetString() == name ) {
                return index;
            }
        }
        return -1;
    }

  public:
    void set_head_range( const float range ) {
        this->_headRange = range;
    }
    float get_head_range() const {
        return this->_headRange;
    }

    void set_body_range( const float range ) {
        this->_bodyRange = range;
    }
    float get_body_range() const {
        return this->_bodyRange;
    }

    void set_eyes_range( const float range ) {
        this->_eyesRange = range;
    }
    float get_eyes_range() const {
        return this->_eyesRange;
    }

    void set_target( const godot::Vector2 &target ) {
        if ( this->_target_point == nullptr ) {
            return;
        }

        this->_target_point->Set( godot::CLAMP<float, float, float>( target.x, -1.0, 1.0 ),
                                  godot::CLAMP<float, float, float>( target.y, -1.0, 1.0 ) );
    }

    godot::Vector2 get_target() const {
        if ( this->_target_point == nullptr ) {
            return godot::Vector2();
        }
        return godot::Vector2( this->_target_point->GetX(), this->_target_point->GetY() );
    }

    virtual void _cubism_init( CubismModelProxy *model ) override {
        this->_target_point = memnew( Csm::CubismTargetPoint );
        this->_target_point->Set( 0.0, 0.0 );
        this->_map_param_idx.Clear();
        this->initialized = false;
    }

    virtual void _cubism_term( CubismModelProxy *model ) override {

        this->_map_param_idx.Clear();

        if ( this->_target_point != nullptr ) {
            godot::memdelete( this->_target_point );
            this->_target_point = nullptr;
        }
    }

    virtual void _cubism_process( CubismModelProxy *model, const float delta ) override {
        if ( this->_target_point == nullptr ) {
            return;
        }
        if ( this->_active == false ) {
            return;
        }

        Csm::CubismModel *_model = model->GetModel();

        if ( this->initialized == false ) {
            Csm::csmInt32 v;
            // ANGLE_X
            v = this->find_idx( _model, Csm::csmString( this->head_angle_x.utf8().ptr() ) );
            if ( v == -1 && this->head_angle_x.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->head_angle_x );
            }
            this->_map_param_idx[HEAD_ANGLE_X] = v;
            // ANGLE_Y
            v = this->find_idx( _model, Csm::csmString( this->head_angle_y.utf8().ptr() ) );
            if ( v == -1 && this->head_angle_y.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->head_angle_y );
            }
            this->_map_param_idx[HEAD_ANGLE_Y] = v;
            // ANGLE_Z
            v = this->find_idx( _model, Csm::csmString( this->head_angle_z.utf8().ptr() ) );
            if ( v == -1 && this->head_angle_z.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->head_angle_z );
            }
            this->_map_param_idx[HEAD_ANGLE_Z] = v;

            // BODY_ANGLE_X
            v = this->find_idx( _model, Csm::csmString( this->body_angle_x.utf8().ptr() ) );
            if ( v == -1 && this->body_angle_x.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->body_angle_x );
            }
            this->_map_param_idx[BODY_ANGLE_X] = v;

            // EYE_BALL_X
            v = this->find_idx( _model, Csm::csmString( this->eyes_ball_x.utf8().ptr() ) );
            if ( v == -1 && this->eyes_ball_x.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->eyes_ball_x );
            }
            this->_map_param_idx[EYES_BALL_X] = v;
            // EYE_BALL_Y
            v = this->find_idx( _model, Csm::csmString( this->eyes_ball_y.utf8().ptr() ) );
            if ( v == -1 && this->eyes_ball_y.length() > 0 ) {
                WARN_PRINT_ED( godot::String( "Undefined parameter name: " ) + this->eyes_ball_y );
            }
            this->_map_param_idx[EYES_BALL_Y] = v;

            this->initialized = true;
        }

        this->_target_point->Update( delta );
        Csm::csmFloat32 _dragX = this->_target_point->GetX();
        Csm::csmFloat32 _dragY = this->_target_point->GetY();

        // Dragging Head
        _model->AddParameterValue( this->_map_param_idx[HEAD_ANGLE_X], _dragX * this->_headRange );
        _model->AddParameterValue( this->_map_param_idx[HEAD_ANGLE_Y], _dragY * this->_headRange );
        _model->AddParameterValue( this->_map_param_idx[HEAD_ANGLE_Z],
                                   _dragX * _dragY * ( this->_headRange * -1 ) );

        // Dragging Body
        _model->AddParameterValue( this->_map_param_idx[BODY_ANGLE_X], _dragX * this->_bodyRange );

        // Dragging Eyes
        _model->AddParameterValue( this->_map_param_idx[EYES_BALL_X], _dragX * this->_eyesRange );
        _model->AddParameterValue( this->_map_param_idx[EYES_BALL_Y], _dragY * this->_eyesRange );
    }
};

#endif // VDOT_CUBISM_EFFECT_TARGET_POINT_H
