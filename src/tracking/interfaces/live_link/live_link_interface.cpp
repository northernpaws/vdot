#include <godot_cpp/variant/utility_functions.hpp>

#include "../../tracking_server.h"

#include "live_link_face_tracker.h"
#include "live_link_interface.h"

LiveLinkInterface *LiveLinkInterface::singleton = nullptr;

LiveLinkInterface *LiveLinkInterface::get_singleton() {
    return singleton;
}

void LiveLinkInterface::_bind_methods() {
    ADD_SIGNAL( godot::MethodInfo(
        "tracker_connected", godot::PropertyInfo( godot::Variant::OBJECT, "tracker",
                                                  godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                  LiveLinkFaceTracker::get_class_static() ) ) );
    ADD_SIGNAL( godot::MethodInfo(
        "tracker_disconnected", godot::PropertyInfo( godot::Variant::OBJECT, "tracker",
                                                     godot::PropertyHint::PROPERTY_HINT_TYPE_STRING,
                                                     LiveLinkFaceTracker::get_class_static() ) ) );

    godot::ClassDB::bind_method( godot::D_METHOD( "initialize" ), &LiveLinkInterface::initialize );
    godot::ClassDB::bind_method( godot::D_METHOD( "uninitialize" ),
                                 &LiveLinkInterface::uninitialize );
    godot::ClassDB::bind_method( godot::D_METHOD( "is_initialized" ),
                                 &LiveLinkInterface::is_initialized );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_server" ), &LiveLinkInterface::get_server );

    ADD_PROPERTY(
        godot::PropertyInfo( godot::Variant::OBJECT, "server", godot::PROPERTY_HINT_TYPE_STRING,
                             LiveLinkServer::get_class_static(), godot::PROPERTY_USAGE_READ_ONLY ),
        "", "get_server" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_trackers" ),
                                 &LiveLinkInterface::get_trackers );

    ADD_PROPERTY( godot::PropertyInfo(
                      godot::Variant::OBJECT, "trackers", godot::PROPERTY_HINT_ARRAY_TYPE,
                      LiveLinkFaceTracker::get_class_static(), godot::PROPERTY_USAGE_READ_ONLY ),
                  "", "get_trackers" );

    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_connected" ),
                                 &LiveLinkInterface::_on_server_client_connected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_disconnected" ),
                                 &LiveLinkInterface::_on_server_client_disconnected );
    godot::ClassDB::bind_method( godot::D_METHOD( "_on_server_client_updated" ),
                                 &LiveLinkInterface::_on_server_client_updated );
}

LiveLinkInterface::LiveLinkInterface() {
    singleton = this;

    _server = godot::Ref<LiveLinkServer>( memnew( LiveLinkServer ) );
    ERR_FAIL_NULL_MSG( _server, "Failed to create LiveLink server" );

    // We'll manually poll instead of in a thread.
    _server->_disable_polling = true;

    _server->connect( "client_connected", godot::Callable( this, "_on_server_client_connected" ) );
    _server->connect( "client_disconnected",
                      godot::Callable( this, "_on_server_client_disconnected" ) );
    _server->connect( "client_updated", godot::Callable( this, "_on_server_client_updated" ) );
}

LiveLinkInterface::~LiveLinkInterface() {
    // Destroy the server.
    //    _server.unref();

    _trackers.clear();
}

bool LiveLinkInterface::is_initialized() {
    return _initialized;
}

bool LiveLinkInterface::initialize() {
    auto err = _server->listen();
    ERR_FAIL_COND_V_MSG( err != godot::OK, false, "Failed to start LiveLink server listener" );

    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_COND_V_MSG( server == nullptr, false, "Tracking server not initialized." );

    godot::UtilityFunctions::print( "Initialized LiveLink facial tracking interface on port ",
                                    _server->get_port() );

    _initialized = true;

    return _initialized;
}

void LiveLinkInterface::uninitialize() {
    // Stop the LiveLink server.
    if ( _server.is_valid() ) {
        if ( auto err = _server->stop(); err != godot::OK ) {
            godot::UtilityFunctions::push_error( "Failed to gracefully stop LiveLink server" );
        }
    }

    // Remove all registered trackers from the tracking server.
    TrackingServer *server = TrackingServer::get_singleton();
    if ( server != nullptr ) {
        for ( auto i = 0; i < _trackers.keys().size(); i++ ) {
            auto key = _trackers.keys()[i];
            godot::Ref<LiveLinkFaceTracker> tracker = _trackers[key];

            emit_signal( "tracker_disconnected", tracker );

            if ( tracker.is_valid() ) {
                server->remove_tracker( tracker );
            }
        }
    }

    _trackers.clear();

    _initialized = false;

    godot::UtilityFunctions::print( "Shut down LiveLink facial tracking interface on port ",
                                    _server->get_port() );
}

void LiveLinkInterface::process() {
    if ( _server.is_valid() ) {
        _server->poll();
    }
}

godot::Ref<LiveLinkServer> LiveLinkInterface::get_server() const {
    return _server;
}

godot::Dictionary LiveLinkInterface::get_trackers() const {
    return _trackers;
}

void LiveLinkInterface::_on_server_client_connected( const godot::Ref<LiveLinkClient> &client ) {
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_NULL_MSG(
        server, "Expected Tracking server to be initialized when adding new LiveLink tracker." );

    // Create a new LiveLink tracker for the new client.
    godot::Ref<LiveLinkFaceTracker> tracker = memnew( LiveLinkFaceTracker( client ) );
    ERR_FAIL_NULL( tracker );

    _trackers[client->_id] = tracker;

    server->add_tracker( tracker );

    emit_signal( "tracker_connected", tracker );

    godot::UtilityFunctions::print( "Added new LiveLink tracker: ", tracker->get_tracker_name() );
}

void LiveLinkInterface::_on_server_client_disconnected( const godot::Ref<LiveLinkClient> &client ) {
    godot::Ref<LiveLinkFaceTracker> tracker = _trackers[client->_id];
    if ( tracker.is_valid() ) {
        godot::UtilityFunctions::print( "Removing disconnected LiveLink tracker: ",
                                        tracker->get_tracker_name() );

        emit_signal( "tracker_disconnected", tracker );

        _trackers.erase( LiveLinkFaceTracker::tracker_name( client ) );

        TrackingServer *server = TrackingServer::get_singleton();
        if ( server != nullptr ) {
            server->remove_tracker( tracker );
        }
    }
}

void LiveLinkInterface::_on_server_client_updated( const godot::Ref<LiveLinkClient> &client ) {
    godot::Ref<LiveLinkFaceTracker> tracker = _trackers[client->_id];
    ERR_FAIL_NULL_MSG( tracker, "LinkLink tracker should have been registered, but wasn't found" );

    // Grab a handle to the updated client data packet.
    auto data = client->_values;

    // We need to convert the ARKit blend shapes to Unified Expression blend shapes.
    // ref:
    // https://github.com/kusomaigo/VRCFaceTracking-LiveLink/blob/736eae437b10ec9dc9e9bbe9cbfed7c7be2bac6a/VRCFT-LiveLink/LiveLinkExtTrackingInterface.cs#L221
    // ref:
    // https://github.com/regzo2/VRCFaceTracking-MeowFace/blob/983564228c2aa83c8a02e710ce6fc3b82f2a02e1/MeowFaceExtTrackingInterface/MeowFaceExtTrackingInterface.cs#L92

    // TODO: eye position decoding
    //  ref:
    //  https://github.com/kusomaigo/VRCFaceTracking-LiveLink/blob/736eae437b10ec9dc9e9bbe9cbfed7c7be2bac6a/VRCFT-LiveLink/LiveLinkExtTrackingInterface.cs#L152

    for ( int i = 0; i < ARKit::BlendShape::Max; i++ ) {
        auto shape = static_cast<ARKit::BlendShape>( i );

        if ( UnifiedExpressions::arkit_to_unified.has( shape ) ) {
            auto weight = data->get_blend_shape( shape );
            auto target = UnifiedExpressions::arkit_to_unified[shape];
            tracker->set_blend_shape( target, weight );
        }
    }
    /*
        // Eye expressions
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_EYE_WIDE_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::EyeWideLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_EYE_WIDE_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::EyeWideRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_EYE_SQUINT_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::EyeSquintLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_EYE_SQUINT_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::EyeSquintRight ) );

        // Brow expressions
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_INNER_UP_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowInnerUp ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_INNER_UP_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowInnerUp ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_OUTER_UP_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowOuterUpLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_OUTER_UP_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowOuterUpRight ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_PINCH_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowDownLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_LOWERER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowDownLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_PINCH_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowDownRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_BROW_LOWERER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::BrowDownRight ) );

        // Jaw expressions
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_JAW_OPEN,
                                  data->get_blend_shape( ARKit::BlendShape::JawOpen ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_JAW_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::JawLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_JAW_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::JawRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_JAW_FORWARD,
                                  data->get_blend_shape( ARKit::BlendShape::JawForward ) );

        // Mouth expression set
        // TODO: reference VRChat module says "using Azmidi's meowface module for
        //  reference", should check that module to verify mappings.
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_CLOSED,
                                  data->get_blend_shape( ARKit::BlendShape::MouthClose ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthRight ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_PULL_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthSmileLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_SLANT_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthSmileLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_PULL_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthSmileRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_CORNER_SLANT_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthSmileRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_FROWN_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFrownLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_FROWN_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFrownRight ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_DOWN_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthLowerDownLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_LOWER_DOWN_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthLowerDownRight ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_UP_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthUpperUpLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_DEEPEN_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthUpperUpLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_UP_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthUpperUpRight ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_UPPER_DEEPEN_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthUpperUpRight ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_RAISER_UPPER,
                                  data->get_blend_shape( ARKit::BlendShape::MouthShrugUpper ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_RAISER_LOWER,
                                  data->get_blend_shape( ARKit::BlendShape::MouthShrugLower ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_DIMPLE_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthDimpleLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_DIMPLE_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthDimpleRight ) );

        // TODO: MouthTightenerLeft, MouthTightenerRight

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_PRESS_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPressLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_MOUTH_PRESS_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPressRight ) );

        // Lip expression set
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_UPPER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPucker ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_LOWER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPucker ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_UPPER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPucker ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_PUCKER_LOWER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthPucker ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_UPPER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFunnel ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_UPPER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFunnel ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_LOWER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFunnel ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_FUNNEL_LOWER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthFunnel ) );

        // ref:
        //
       https://github.com/kusomaigo/VRCFaceTracking-LiveLink/blob/736eae437b10ec9dc9e9bbe9cbfed7c7be2bac6a/VRCFT-LiveLink/LiveLinkExtTrackingInterface.cs#L283C83-L283C200
        tracker->set_blend_shape(
            UnifiedExpressions::BlendShape::FT_LIP_SUCK_UPPER_LEFT,
            std::min( 1.0f -
                          (float)std::pow( data->get_blend_shape(
       ARKit::BlendShape::MouthUpperUpLeft ), 1.0f / 6.0f ), data->get_blend_shape(
       ARKit::BlendShape::MouthRollUpper ) ) ); tracker->set_blend_shape(
            UnifiedExpressions::BlendShape::FT_LIP_SUCK_UPPER_RIGHT,
            std::min(
                1.0f - (float)std::pow( data->get_blend_shape( ARKit::BlendShape::MouthUpperUpRight
       ), 1.0f / 6.0f ), data->get_blend_shape( ARKit::BlendShape::MouthRollUpper ) ) );

        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_SUCK_LOWER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthRollLower ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_LIP_SUCK_LOWER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::MouthRollLower ) );

        // Cheek expression set
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_CHEEK_PUFF_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::CheekPuff ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_CHEEK_PUFF_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::CheekPuff ) );
        // unifiedExpressions[(int)UnifiedExpressions.CheekSuckLeft].Weight =
        // trackingData.lowerface.CheekPuff;
        // unifiedExpressions[(int)UnifiedExpressions.CheekSuckRight].Weight =
        // trackingData.lowerface.CheekPuff;
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_CHEEK_SQUINT_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::CheekSquintLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_CHEEK_SQUINT_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::CheekSquintRight ) );

        // Nose expression set
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_NOSE_SNEER_LEFT,
                                  data->get_blend_shape( ARKit::BlendShape::NoseSneerLeft ) );
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_NOSE_SNEER_RIGHT,
                                  data->get_blend_shape( ARKit::BlendShape::NoseSneerRight ) );

        // Tongue expression set
        tracker->set_blend_shape( UnifiedExpressions::BlendShape::FT_TONGUE_OUT,
                                  data->get_blend_shape( ARKit::BlendShape::TongueOut ) );
    */
    tracker->emit_signal( "blend_shapes_updated" );

    // TODO: process tracker data
}
