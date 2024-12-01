// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_EYE_BLINK_H
#define VDOT_CUBISM_EFFECT_EYE_BLINK_H

#include "cubism.h"

#include "cubism_effect.h"

#include "renderer/cubism_model_proxy.h"

class CubismEffectEyeBlink : public CubismEffect {
    GDCLASS( CubismEffectEyeBlink, CubismEffect )

  protected:
    static void _bind_methods() {
    }

  private:
    Csm::CubismEyeBlink *_eye_blink = nullptr;

  public:
    virtual void _cubism_init( CubismModelProxy *model ) override {
        Csm::ICubismModelSetting *_model_setting = model->_model_setting;
        if ( _model_setting->GetEyeBlinkParameterCount() == 0 ) {
            return;
        }
        this->_eye_blink = Csm::CubismEyeBlink::Create( _model_setting );
    }

    virtual void _cubism_term( CubismModelProxy *model ) override {
        if ( this->_eye_blink != nullptr ) {
            Csm::CubismEyeBlink::Delete( this->_eye_blink );
            this->_eye_blink = nullptr;
        }
    }

    virtual void _cubism_process( CubismModelProxy *model, const float delta ) override {
        if ( this->_eye_blink == nullptr ) {
            return;
        }
        if ( this->_active == false ) {
            return;
        }

        this->_eye_blink->UpdateParameters( model->GetModel(), delta );
    }
};

#endif // VDOT_CUBISM_EFFECT_EYE_BLINK_H
