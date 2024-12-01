// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_PRINT_H
#define VDOT_CUBISM_PRINT_H

#include "../cubism.h"

#ifdef WINDOWS_ENABLED
#include <stdarg.h>
#include <stdio.h>
#endif // WINDOWS_ENABLED
#include <string>

#include <godot_cpp/core/class_db.hpp>

#include <CubismFramework.hpp>

void PrintLog( const Csm::csmChar *format, ... ) {
#ifdef DEBUG_ENABLED
    va_list args;
    Csm::csmChar buf[MAX_PRINTLOG_LENGTH];
    va_start( args, format );
    vsnprintf( buf, sizeof( buf ), format, args );
    WARN_PRINT( buf );
    va_end( args );
#endif // DEBUG_ENABLED
}

void PrintMessage( const Csm::csmChar *message ) {
#ifdef DEBUG_ENABLED
    PrintLog( "%s", message );
#endif // DEBUG_ENABLED
}

#endif // VDOT_CUBISM_PRINT_H
