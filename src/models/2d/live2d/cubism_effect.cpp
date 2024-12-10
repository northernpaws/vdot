// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#include "cubism_effect.h"

void CubismEffect::_bind_methods() {
    godot::ClassDB::bind_method( godot::D_METHOD( "set_active", "value" ),
                                 &CubismEffect::set_active );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_active" ), &CubismEffect::get_active );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::BOOL, "active" ), "set_active",
                  "get_active" );
}

void CubismEffect::_cubism_init( CubismModelProxy *model ) {
}

void CubismEffect::_cubism_term( CubismModelProxy *model ) {
}

void CubismEffect::_cubism_prologue( CubismModelProxy *model, const float delta ) {
}
void CubismEffect::_cubism_process( CubismModelProxy *model, const float delta ) {
}
void CubismEffect::_cubism_epilogue( CubismModelProxy *model, const float delta ) {
}

void CubismEffect::_enter_tree() {
    auto *node = godot::Object::cast_to<CubismModel>( this->get_parent() );
    if ( node != nullptr ) {
        node->_on_append_child_act( this );
    }
}

void CubismEffect::_exit_tree() {
    auto *node = godot::Object::cast_to<CubismModel>( this->get_parent() );
    if ( node != nullptr ) {
        node->_on_remove_child_act( this );
    }
}
