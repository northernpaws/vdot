// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_MOTION_ENTRY_H
#define VDOT_CUBISM_MOTION_ENTRY_H

#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/classes/resource.hpp>

#include <CubismFramework.hpp>
#include <Motion/CubismExpressionMotionManager.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>

class CubismModelProxy;
class CubismModel;

class CubismMotionQueueEntryHandle : public godot::Resource {
    GDCLASS(CubismMotionQueueEntryHandle, godot::Resource)
    friend CubismModel;

public:
    enum HandleError {
        OK = godot::Error::OK,
        FAILED = godot::Error::FAILED
    };

protected:
    static void _bind_methods() {
        godot::ClassDB::bind_method(godot::D_METHOD("get_error"), &CubismMotionQueueEntryHandle::get_error);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "error"), "", "get_error");

        BIND_ENUM_CONSTANT(OK);
        BIND_ENUM_CONSTANT(FAILED);
    }

public:
    HandleError get_error() const {
        if(this->_handle == Csm::InvalidMotionQueueEntryHandleValue) return FAILED;

        return OK;
    }


private:
    Csm::CubismMotionQueueEntryHandle _handle = Csm::InvalidMotionQueueEntryHandleValue;
};

VARIANT_ENUM_CAST(CubismMotionQueueEntryHandle::HandleError);

class CubismMotionEntry : public godot::Resource {
    GDCLASS(CubismMotionEntry, godot::Resource)
    friend CubismModel;

protected:
    static void _bind_methods() {}

private:
    Csm::CubismMotionQueueEntry *_entry;
};


#endif // VDOT_CUBISM_MOTION_ENTRY_H
