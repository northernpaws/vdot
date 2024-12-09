// Copied from godot-cpp/test/src and modified.

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "vdot.h"

#include <CubismFramework.hpp>
#include <godot_cpp/classes/os.hpp>

#include "models/live2d/cubism_effect.h"
#include "models/live2d/cubism_effect_breath.h"
#include "models/live2d/cubism_effect_custom.h"
#include "models/live2d/cubism_effect_eye_blink.h"
#include "models/live2d/cubism_effect_hit_area.h"
#include "models/live2d/cubism_effect_target_point.h"
#include "models/live2d/cubism_model.h"
#include "models/live2d/cubism_motion_entry.h"
#include "models/live2d/cubism_value_abs.h"
#include "models/live2d/cubism_value_parameter.h"
#include "models/live2d/cubism_value_part_opacity.h"
#include "models/live2d/renderer/cubism_allocator.h"

#include "tracking/tracker.h"
#include "tracking/tracker_face.h"
#include "tracking/tracking_interface.h"
#include "tracking/tracking_server.h"

#include "tracking/editor/editor_plugin.h"
#include "tracking/editor/trackers/face_tracker_panel.h"

#include "tracking/interfaces/live_link/editor_plugin.h"
#include "tracking/interfaces/live_link/live_link_face_tracker.h"
#include "tracking/interfaces/live_link/live_link_interface.h"
#include "tracking/interfaces/live_link/live_link_panel.h"
#include "tracking/interfaces/live_link/live_link_server.h"

#include "tracking/interfaces/vts/vts_interface.h"

using namespace godot;

static CubismAllocator cubism_allocator;
static Csm::CubismFramework::Option csm_options;

/// @file
/// Register our classes with Godot.

void cubism_output( const char *message ) {
    WARN_PRINT( message );
}

static TrackingServer *tracking_server = nullptr;

static godot::Ref<LiveLinkInterface> live_link_interface = nullptr;
static godot::Ref<VTSInterface> vts_interface = nullptr;

namespace {
    /// @brief Called by Godot to let us register our classes with Godot.
    ///
    /// @param p_level the level being initialized by Godot
    ///
    /// @see GDExtensionInit
    void initializeExtension( ModuleInitializationLevel p_level ) {
        if ( p_level == MODULE_INITIALIZATION_LEVEL_SERVERS ) {
            ARKit::_init_arkit_shape_names();

            GDREGISTER_ABSTRACT_CLASS( Tracker )
            GDREGISTER_CLASS( FaceTracker )

            GDREGISTER_ABSTRACT_CLASS( TrackingInterface )
            GDREGISTER_CLASS( TrackingServer )
        }

        if ( p_level == MODULE_INITIALIZATION_LEVEL_SCENE ) {
            // Register the tracking server as a singleton.
            //
            // NOTE: Singleton registration isn't available in the
            //  server initialization level, so we perform it here.
            tracking_server = memnew( TrackingServer );
            Engine::get_singleton()->register_singleton( "TrackingServer",
                                                         TrackingServer::get_singleton() );

            //            ClassDB::register_class<ExampleRef>();
            //            ClassDB::register_class<ExampleMin>();
            //            ClassDB::register_class<Example>();
            //            ClassDB::register_class<ExampleVirtual>( true );
            //            ClassDB::register_abstract_class<ExampleAbstract>();

            ClassDB::register_class<VDot>();

            // ====================
            // LiveLinkFace Tracking

            ClassDB::register_class<LiveLinkClientData>();
            ClassDB::register_class<LiveLinkClient>();
            ClassDB::register_class<LiveLinkServer>();

            // tracking interface
            ClassDB::register_class<LiveLinkInterface>();
            ClassDB::register_class<LiveLinkFaceTracker>();

            // Add the LiveLink interface to the tracking interfaces list.
            live_link_interface.instantiate();
            tracking_server->add_interface( live_link_interface );
            Engine::get_singleton()->register_singleton( "LiveLinkInterface",
                                                         LiveLinkInterface::get_singleton() );

            ClassDB::register_class<VTSInterface>();
            ClassDB::register_class<VTSFaceTracker>();

            // Add the VTS interface, and register it as a scripting singleton so that
            //  scripts can call it to initialize and connect to new VTS trackers.
            vts_interface.instantiate();
            tracking_server->add_interface( vts_interface );
            Engine::get_singleton()->register_singleton( "VTSInterface",
                                                         VTSInterface::get_singleton() );

            // A little hacky, but the best way we were able to find
            //  to inject a process loop call for the tracking server.
//            auto* main_loop = godot::Engine::get_singleton()->get_main_loop();
//            auto* scene_tree = godot::Object::cast_to<godot::SceneTree>(main_loop);
//            scene_tree->connect("process_frame", godot::Callable(tracking_server, "_process"));

            // ====================
            // Live2D Models

            csm_options.LogFunction = cubism_output;
#ifdef DEBUG_ENABLED
            csm_options.LoggingLevel = Csm::CubismFramework::Option::LogLevel::LogLevel_Verbose;
#else
            csm_options.LoggingLevel = Csm::CubismFramework::Option::LogLevel::LogLevel_Warning;
#endif // DEBUG_ENABLED

            // Initialize the Cubism framework before registering it's resources.
            Csm::CubismFramework::StartUp( &cubism_allocator, &csm_options );
            Csm::CubismFramework::Initialize();

            GDREGISTER_VIRTUAL_CLASS( CubismEffect )
            GDREGISTER_CLASS( CubismEffectBreath )
            GDREGISTER_CLASS( CubismEffectCustom )
            GDREGISTER_CLASS( CubismEffectEyeBlink )
            GDREGISTER_CLASS( CubismEffectHitArea )
            GDREGISTER_CLASS( CubismEffectTargetPoint )

            GDREGISTER_VIRTUAL_CLASS( CubismValueAbs )
            GDREGISTER_CLASS( CubismParameter )
            GDREGISTER_CLASS( CubismPartOpacity )

            GDREGISTER_CLASS( CubismMotionQueueEntryHandle )
            GDREGISTER_CLASS( CubismMotionEntry )
            GDREGISTER_CLASS( CubismModel )
        }

        if ( p_level == MODULE_INITIALIZATION_LEVEL_EDITOR ) {
            GDREGISTER_CLASS( TrackingEditorPlugin )
            GDREGISTER_CLASS( TrackingPluginPanel )
            GDREGISTER_CLASS( FaceTrackerPanel )
            EditorPlugins::add_by_type<TrackingEditorPlugin>();

            GDREGISTER_CLASS( LiveLinkPanel )
            GDREGISTER_CLASS( LiveLinkEditorPlugin )

            EditorPlugins::add_by_type<LiveLinkEditorPlugin>();
        }
    }

    /// @brief Called by Godot to let us do any cleanup.
    ///
    /// @see GDExtensionInit
    void uninitializeExtension( ModuleInitializationLevel p_level ) {
        if ( p_level == MODULE_INITIALIZATION_LEVEL_SCENE ) {
            Csm::CubismFramework::Dispose();

            Engine::get_singleton()->unregister_singleton( "TrackingServer" );
            memdelete( tracking_server );
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
GDExtensionBool GDE_EXPORT GDExtensionInit( GDExtensionInterfaceGetProcAddress p_get_proc_address,
                                            GDExtensionClassLibraryPtr p_library,
                                            GDExtensionInitialization *r_initialization ) {
    {
        GDExtensionBinding::InitObject init_obj( p_get_proc_address, p_library, r_initialization );

        init_obj.register_initializer( initializeExtension );
        init_obj.register_terminator( uninitializeExtension );
        init_obj.set_minimum_library_initialization_level( MODULE_INITIALIZATION_LEVEL_SERVERS );

        return init_obj.init();
    }
}
}
