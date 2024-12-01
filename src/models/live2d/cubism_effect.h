// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_EFFECT_H
#define VDOT_CUBISM_EFFECT_H

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>

#include "cubism.h"

#include "cubism_model.h"

class CubismModelProxy;

class CubismEffect : public godot::Node {
    GDCLASS( CubismEffect, godot::Node )

  protected:
    bool _active = true;

  protected:
    static void _bind_methods();

  public:
    void set_active( const bool active ) {
        this->_active = active;
    }
    bool get_active() const {
        return this->_active;
    }

    virtual void _cubism_init( CubismModelProxy *model );
    virtual void _cubism_term( CubismModelProxy *model );
    virtual void _cubism_prologue( CubismModelProxy *model, const float delta );
    virtual void _cubism_process( CubismModelProxy *model, const float delta );
    virtual void _cubism_epilogue( CubismModelProxy *model, const float delta );

    void _enter_tree() override;
    void _exit_tree() override;
};

#endif // VDOT_CUBISM_EFFECT_H
