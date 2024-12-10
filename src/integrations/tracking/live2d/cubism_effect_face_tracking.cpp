
#include "cubism_effect_face_tracking.h"

void CubismEffectFaceTracking::_bind_methods() {
    godot::ClassDB::bind_method(
        godot::D_METHOD( "_server_tracker_added", "tracker_name", "tracker_type" ),
        &CubismEffectFaceTracking::_server_tracker_added );
}

CubismEffectFaceTracking::CubismEffectFaceTracking() {
}

void CubismEffectFaceTracking::_enter_tree() {
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_COND_MSG( server == nullptr, "Expected tracking server to be initialized." );

    server->connect( "tracker_added", godot::Callable( this, "_server_tracker_added" ) );
}

void CubismEffectFaceTracking::_exit_tree() {
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_COND_MSG( server == nullptr, "Expected tracking server to be initialized." );

    server->disconnect( "tracker_added", godot::Callable( this, "_server_tracker_added" ) );
}

void CubismEffectFaceTracking::_cubism_init( CubismModelProxy *model ) {
}

void CubismEffectFaceTracking::_cubism_term( CubismModelProxy *model ) {
}

void CubismEffectFaceTracking::_cubism_process( CubismModelProxy *model, const float delta ) {
    if ( !_tracker.is_valid() ) {
        return; // no-op if we don't have a tracker assigned
    }

    if ( model == nullptr ) {
        return;
    }

    //    model->_model_setting->GetEyeBlinkParameterCount()
    /* Csm::CubismModel * csm_model = model->GetModel();

     auto left_eye = _tracker->get_blend_shape(UnifiedExpressions::FT_EYE_CLOSED_LEFT);
     auto right_eye = _tracker->get_blend_shape(UnifiedExpressions::FT_EYE_CLOSED_RIGHT);

     for (Live2D::Cubism::Framework::csmUint32 i = 0; i < model->_list_eye_blink.GetSize(); ++i) {
         auto param_index = csm_model->GetParameterIndex(model->_list_eye_blink[i]);
         auto minimum_value = csm_model->GetParameterMinimumValue(param_index);
         auto maximum_value = csm_model->GetParameterMaximumValue(param_index);

         // TODO: eye tracking parameter
 //        csm_model->SetParameterValue(model->_list_eye_blink [i], parameterValue);
     }*/

    //    model->_list_eye_blink // eye parameter list
}

bool CubismEffectFaceTracking::_set( const godot::StringName &p_name,
                                     const godot::Variant &p_property ) {
    if ( p_name == godot::StringName( "tracker" ) ) {
        TrackingServer *server = TrackingServer::get_singleton();
        ERR_FAIL_COND_V_MSG( server == nullptr, false,
                             "Expected tracking server to be initialized." );

        auto tracker = server->get_tracker( p_name );
        _tracker = tracker;

        return true;
    }

    return false;
}

bool CubismEffectFaceTracking::_get( const godot::StringName &p_name,
                                     godot::Variant &r_property ) const {
    if ( p_name == godot::StringName( "tracker" ) ) {
        if ( _tracker.is_valid() ) {
            r_property = _tracker->get_tracker_name();
        } else {
            r_property = godot::StringName( "" );
        }
        return true;
    }

    return false;
}

void CubismEffectFaceTracking::_get_property_list(
    godot::List<godot::PropertyInfo> *p_list ) const {
    TrackingServer *server = TrackingServer::get_singleton();
    ERR_FAIL_COND_MSG( server == nullptr, "Expected tracking server to be initialized." );

    godot::PropertyInfo tracker_prop;
    tracker_prop.name = "tracker";
    tracker_prop.type = godot::Variant::INT;
    tracker_prop.hint = godot::PROPERTY_HINT_ENUM;
    tracker_prop.hint_string = "";

    auto trackers = server->get_trackers( TrackingServer::TrackerType::TRACKER_FACE );
    auto keys = trackers.keys();
    for ( int i = 0; i < keys.size(); i++ ) {
        auto key = keys[i];
        auto tracker = trackers[key];

        tracker_prop.hint_string = tracker_prop.hint_string + ",";
    }

    p_list->push_back( tracker_prop );
}

void CubismEffectFaceTracking::_server_tracker_added( const godot::StringName &p_tracker_name,
                                                      TrackingServer::TrackerType p_tracker_type ) {
    // Need to refresh the tracker name enum with the new list.
    notify_property_list_changed();
}