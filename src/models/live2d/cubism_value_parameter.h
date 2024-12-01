// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_VALUE_PARAMETER_H
#define VDOT_CUBISM_VALUE_PARAMETER_H

#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/classes/resource.hpp>

#include <CubismFramework.hpp>
#include <Motion/CubismExpressionMotionManager.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>

#include "cubism_value_abs.h"

class InternalCubismUserModel;
class CubismModel;

class CubismParameter : public CubismValueAbs {
    GDCLASS(CubismParameter, CubismValueAbs)
    friend CubismModel;

public:
    enum Type {
        NORMAL = 0,
        BLEND_SHAPE = 1
    };

private:
    CubismParameter::Type type;
    float minimum_value;
    float maximum_value;
    float default_value;
    bool hold;

protected:
    static void _bind_methods() {

        godot::ClassDB::bind_method(godot::D_METHOD("get_minimum_value"), &CubismParameter::get_minimum_value);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "minimum_value"), godot::String(), "get_minimum_value");
        godot::ClassDB::bind_method(godot::D_METHOD("get_maximum_value"), &CubismParameter::get_maximum_value);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "maximum_value"), godot::String(), "get_maximum_value");
        godot::ClassDB::bind_method(godot::D_METHOD("get_default_value"), &CubismParameter::get_default_value);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "default_value"), godot::String(), "get_default_value");

        godot::ClassDB::bind_method(godot::D_METHOD("set_hold"), &CubismParameter::set_hold);
        godot::ClassDB::bind_method(godot::D_METHOD("get_hold"), &CubismParameter::get_hold);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::BOOL, "hold"), "set_hold", "get_hold");

        godot::ClassDB::bind_method(godot::D_METHOD("reset"), &CubismParameter::reset);

        BIND_ENUM_CONSTANT(NORMAL);
        BIND_ENUM_CONSTANT(BLEND_SHAPE);
    }

private:
    void setup(Csm::CubismModel *model, Csm::csmInt32 index) override {
        Live2D::Cubism::Core::csmModel *csm_model = model->GetModel();

        this->id = godot::String(Live2D::Cubism::Core::csmGetParameterIds(csm_model)[index]);
        this->_value = Live2D::Cubism::Core::csmGetParameterValues(csm_model)[index];
        this->raw_value = &(Live2D::Cubism::Core::csmGetParameterValues(csm_model)[index]);
        this->changed = false;

        this->type = static_cast<Type>(Live2D::Cubism::Core::csmGetParameterTypes(csm_model)[index]);
        this->minimum_value = Live2D::Cubism::Core::csmGetParameterMinimumValues(csm_model)[index];
        this->maximum_value = Live2D::Cubism::Core::csmGetParameterMaximumValues(csm_model)[index];
        this->default_value = Live2D::Cubism::Core::csmGetParameterDefaultValues(csm_model)[index];
        this->hold = false;
    }

public:
    CubismParameter() : CubismValueAbs(CubismValueAbs::ValueType::PARAMETER) {}

    void reset() { this->set_value(this->default_value); this->hold = false; }
    float get_minimum_value() const { return this->minimum_value; }
    float get_maximum_value() const { return this->maximum_value; }
    float get_default_value() const { return this->default_value; }

    void set_hold(const bool value) { this->hold = value; }
    bool get_hold() const { return this->hold; }
};

VARIANT_ENUM_CAST(CubismParameter::Type);

#endif // VDOT_CUBISM_VALUE_PARAMETER_H
