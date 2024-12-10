// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_VALUE_PART_OPACITY_H
#define VDOT_CUBISM_VALUE_PART_OPACITY_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/property_info.hpp>

#include <CubismFramework.hpp>
#include <Motion/CubismExpressionMotionManager.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>

#include "cubism_value_abs.h"

class InternalCubismUserModel;
class CubismModel;

class CubismPartOpacity : public CubismValueAbs {
    GDCLASS( CubismPartOpacity, CubismValueAbs )
    friend CubismModel;

  protected:
    static void _bind_methods() {
    }

  private:
    void setup( Csm::CubismModel *model, Csm::csmInt32 index ) override {
        Live2D::Cubism::Core::csmModel *csm_model = model->GetModel();

        this->id = godot::String( Live2D::Cubism::Core::csmGetPartIds( csm_model )[index] );
        this->_value = Live2D::Cubism::Core::csmGetPartOpacities( csm_model )[index];
        this->raw_value = &( Live2D::Cubism::Core::csmGetPartOpacities( csm_model )[index] );
        this->changed = false;
    }

  public:
    CubismPartOpacity() : CubismValueAbs( CubismValueAbs::ValueType::PART_OPACITY ) {
    }
};

#endif // VDOT_CUBISM_VALUE_PART_OPACITY_H
