// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_CUSTOM_H
#define VDOT_CUBISM_EFFECT_CUSTOM_H

#include "cubism.h"

#include "cubism_effect.h"
#include "renderer/cubism_model_proxy.h"

class CubismEffectCustom : public CubismEffect {
    GDCLASS(CubismEffectCustom, CubismEffect)

protected:
    static void _bind_methods() {
        ADD_SIGNAL(godot::MethodInfo("cubism_init", godot::PropertyInfo(godot::Variant::OBJECT, "model", godot::PROPERTY_HINT_RESOURCE_TYPE, "GDCubismUserModel")));
        ADD_SIGNAL(godot::MethodInfo("cubism_term", godot::PropertyInfo(godot::Variant::OBJECT, "model", godot::PROPERTY_HINT_RESOURCE_TYPE, "GDCubismUserModel")));

        ADD_SIGNAL(godot::MethodInfo("cubism_prologue", godot::PropertyInfo(godot::Variant::OBJECT, "model", godot::PROPERTY_HINT_RESOURCE_TYPE, "GDCubismUserModel"), godot::PropertyInfo(godot::Variant::FLOAT, "delta")));
        ADD_SIGNAL(godot::MethodInfo("cubism_process", godot::PropertyInfo(godot::Variant::OBJECT, "model", godot::PROPERTY_HINT_RESOURCE_TYPE, "GDCubismUserModel"), godot::PropertyInfo(godot::Variant::FLOAT, "delta")));
        ADD_SIGNAL(godot::MethodInfo("cubism_epilogue", godot::PropertyInfo(godot::Variant::OBJECT, "model", godot::PROPERTY_HINT_RESOURCE_TYPE, "GDCubismUserModel"), godot::PropertyInfo(godot::Variant::FLOAT, "delta")));
    }

public:
    virtual void _cubism_init(CubismModelProxy* model) override {
        this->emit_signal("cubism_init", model->_owner_viewport);
    }

    virtual void _cubism_term(CubismModelProxy* model) override {
        this->emit_signal("cubism_term", model->_owner_viewport);
    }

    virtual void _cubism_prologue(CubismModelProxy* model, const float delta) override {
        if(this->_active == false) return;
        this->emit_signal("cubism_prologue", model->_owner_viewport, delta);
    }

    virtual void _cubism_process(CubismModelProxy* model, const float delta) override {
        if(this->_active == false) return;
        this->emit_signal("cubism_process", model->_owner_viewport, delta);
    }

    virtual void _cubism_epilogue(CubismModelProxy* model, const float delta) override {
        if(this->_active == false) return;
        this->emit_signal("cubism_epilogue", model->_owner_viewport, delta);
    }
};


#endif // VDOT_CUBISM_EFFECT_CUSTOM_H
