// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_BREATH_H
#define VDOT_CUBISM_EFFECT_BREATH_H

#include "cubism.h"

#include <CubismFramework.hpp>
#include <CubismDefaultParameterId.hpp>
#include <Id/CubismIdManager.hpp>

#include "renderer/cubism_model_proxy.h"
#include "cubism_effect.h"

class CubismEffectBreath : public CubismEffect {
    GDCLASS(CubismEffectBreath, CubismEffect)

protected:
    static void _bind_methods() {}

private:
    Csm::CubismBreath* _breath = nullptr;

public:
    virtual void _cubism_init(CubismModelProxy* model) override {
        this->_breath = Csm::CubismBreath::Create();

        Csm::csmVector<Csm::CubismBreath::BreathParameterData> param;

        param.PushBack(Csm::CubismBreath::BreathParameterData(Live2D::Cubism::Framework::CubismFramework::GetIdManager()->GetId(Live2D::Cubism::Framework::DefaultParameterId::ParamAngleX), 0.0f, 15.0f, 6.5345f, 0.5f));
        param.PushBack(Csm::CubismBreath::BreathParameterData(Live2D::Cubism::Framework::CubismFramework::GetIdManager()->GetId(Live2D::Cubism::Framework::DefaultParameterId::ParamAngleY), 0.0f, 8.0f, 3.5345f, 0.5f));
        param.PushBack(Csm::CubismBreath::BreathParameterData(Live2D::Cubism::Framework::CubismFramework::GetIdManager()->GetId(Live2D::Cubism::Framework::DefaultParameterId::ParamAngleZ), 0.0f, 10.0f, 5.5345f, 0.5f));
        param.PushBack(Csm::CubismBreath::BreathParameterData(Live2D::Cubism::Framework::CubismFramework::GetIdManager()->GetId(Live2D::Cubism::Framework::DefaultParameterId::ParamBodyAngleX), 0.0f, 4.0f, 15.5345f, 0.5f));
        param.PushBack(Csm::CubismBreath::BreathParameterData(Live2D::Cubism::Framework::CubismFramework::GetIdManager()->GetId(Live2D::Cubism::Framework::DefaultParameterId::ParamBreath), 0.5f, 0.5f, 3.2345f, 0.5f));

        this->_breath->SetParameters(param);
    }

    virtual void _cubism_term(CubismModelProxy* model) override {
        if(this->_breath != nullptr) {
            Csm::CubismBreath::Delete(this->_breath);
            this->_breath = nullptr;
        }
    }

    virtual void _cubism_process(CubismModelProxy* model, const float delta) override {
        if(this->_breath == nullptr) return;
        if(this->_active == false) return;
        this->_breath->UpdateParameters(model->GetModel(), delta);
    }
};


#endif // VDOT_CUBISM_EFFECT_BREATH_H