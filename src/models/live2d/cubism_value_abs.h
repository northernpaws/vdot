// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_VALUE_ABS_H
#define VDOT_CUBISM_VALUE_ABS_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/property_info.hpp>

#include <CubismFramework.hpp>
#include <Motion/CubismExpressionMotionManager.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>

class InternalCubismUserModel;
class CubismModel;

class CubismValueAbs : public godot::Resource {
    GDCLASS( CubismValueAbs, godot::Resource )
    friend CubismModel;

  public:
    enum ValueType { UNKONWN = 0, PARAMETER = 1, PART_OPACITY = 2 };

  protected:
    static void _bind_methods() {
        godot::ClassDB::bind_method( godot::D_METHOD( "get_id" ), &CubismValueAbs::get_id );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::STRING, "id" ), godot::String(),
                      "get_id" );

        godot::ClassDB::bind_method( godot::D_METHOD( "set_value" ), &CubismValueAbs::set_value );
        godot::ClassDB::bind_method( godot::D_METHOD( "get_value" ), &CubismValueAbs::get_value );
        ADD_PROPERTY( godot::PropertyInfo( godot::Variant::FLOAT, "value" ), "set_value",
                      "get_value" );
    }

  protected:
    godot::String id;
    float _value = 0;
    float *raw_value = nullptr;
    bool changed;
    const ValueType _value_type = UNKONWN;

  private:
    virtual void setup( Csm::CubismModel *model, Csm::csmInt32 index ) {
    }

  public:
    CubismValueAbs() = default;
    explicit CubismValueAbs( const ValueType value_type ) : _value_type( value_type ) {
    }

    [[nodiscard]] godot::String get_id() const {
        return this->id;
    }
    void set_value( const float value ) {
        this->_value = value;
        this->changed = true;
    }
    float get_value() const {
        return this->_value;
    }

    void set_raw_value() {
        if ( this->changed ) {
            *this->raw_value = this->_value;
            this->changed = false;
        }
    }

    void get_raw_value() {
        this->_value = *this->raw_value;
    }
};

#endif // VDOT_CUBISM_VALUE_ABS_H
