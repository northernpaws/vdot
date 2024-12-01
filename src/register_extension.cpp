// Copied from godot-cpp/test/src and modified.

#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "vdot.h"

#include "tracking/live_link/live_link_server.h"
#include "tracking/live_link/live_link_panel.h"

#include <CubismFramework.hpp>

#include "models/live2d/renderer/cubism_allocator.h"
#include "models/live2d/cubism_effect.h"
#include "models/live2d/cubism_effect_breath.h"
#include "models/live2d/cubism_effect_custom.h"
#include "models/live2d/cubism_effect_eye_blink.h"
#include "models/live2d/cubism_effect_hit_area.h"
#include "models/live2d/cubism_effect_target_point.h"
#include "models/live2d/cubism_motion_entry.h"
#include "models/live2d/cubism_value_abs.h"
#include "models/live2d/cubism_value_parameter.h"
#include "models/live2d/cubism_value_part_opacity.h"
#include "models/live2d/cubism_model.h"

static CubismAllocator cubism_allocator;
static Csm::CubismFramework::Option csm_options;

/// @file
/// Register our classes with Godot.

void cubism_output(const char* message) {
#ifdef DEBUG_ENABLED
    WARN_PRINT(message);
#endif // DEBUG_ENABLED
}

namespace {
    /// @brief Called by Godot to let us register our classes with Godot.
    ///
    /// @param p_level the level being initialized by Godot
    ///
    /// @see GDExtensionInit
    void initializeExtension( godot::ModuleInitializationLevel p_level ) {
        if ( p_level == godot::MODULE_INITIALIZATION_LEVEL_SCENE ) {
//            godot::ClassDB::register_class<ExampleRef>();
//            godot::ClassDB::register_class<ExampleMin>();
//            godot::ClassDB::register_class<Example>();
//            godot::ClassDB::register_class<ExampleVirtual>( true );
//            godot::ClassDB::register_abstract_class<ExampleAbstract>();

            godot::ClassDB::register_class<VDot>();

            // ====================
            // LiveLinkFace Tracking

            godot::ClassDB::register_class<LiveLinkClientData>();
            godot::ClassDB::register_class<LiveLinkClient>();
            godot::ClassDB::register_class<LiveLinkServer>();

            godot::ClassDB::register_class<LiveLinkPanel>();


            // ====================
            // Live2D Models

            csm_options.LogFunction = cubism_output;
#ifdef DEBUG_ENABLED
            csm_options.LoggingLevel = Csm::CubismFramework::Option::LogLevel::LogLevel_Verbose;
#else
            option.LoggingLevel = Csm::CubismFramework::Option::LogLevel::LogLevel_Off;
#endif // DEBUG_ENABLED

            // Initialize the Cubism framework before registering it's resources.
            Csm::CubismFramework::StartUp(&cubism_allocator, &csm_options);
            Csm::CubismFramework::Initialize();

            godot::GDREGISTER_VIRTUAL_CLASS(CubismEffect);
            godot::GDREGISTER_CLASS(CubismEffectBreath);
            godot::GDREGISTER_CLASS(CubismEffectCustom);
            godot::GDREGISTER_CLASS(CubismEffectEyeBlink);
            godot::GDREGISTER_CLASS(CubismEffectHitArea);
            godot::GDREGISTER_CLASS(CubismEffectTargetPoint);

            godot::GDREGISTER_VIRTUAL_CLASS(CubismValueAbs);
            godot::GDREGISTER_CLASS(CubismParameter);
            godot::GDREGISTER_CLASS(CubismPartOpacity);

            godot::GDREGISTER_CLASS(CubismMotionQueueEntryHandle);
            godot::GDREGISTER_CLASS(CubismMotionEntry);
            godot::GDREGISTER_CLASS(CubismModel);

        }
    }

    /// @brief Called by Godot to let us do any cleanup.
    ///
    /// @see GDExtensionInit
    void uninitializeExtension( godot::ModuleInitializationLevel p_level ) {
        if ( p_level == godot::MODULE_INITIALIZATION_LEVEL_SCENE ) {
            Csm::CubismFramework::Dispose();
        }
    }
}

extern "C" {
    /// @brief This is the entry point for the shared library.
    ///
    /// @note The name of this function must match the "entry_symbol" in
    /// templates/template.*.gdextension.in
    ///
    /// @param p_get_proc_address the interface (need more info)
    /// @param p_library the library (need more info)
    /// @param r_initialization the intialization (need more info)
    ///
    /// @returns GDExtensionBool
    GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization ) {
        {
            godot::GDExtensionBinding::InitObject init_obj( p_get_proc_address, p_library,
                                                            r_initialization );

            init_obj.register_initializer( initializeExtension );
            init_obj.register_terminator( uninitializeExtension );
            init_obj.set_minimum_library_initialization_level(
                godot::MODULE_INITIALIZATION_LEVEL_SCENE );

            return init_obj.init();
        }
    }
}
