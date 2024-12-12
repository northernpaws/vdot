

#include "lipsync_server.h"
#include "parameters/parameter_context.h"
#include "parameters/parameter_server.h"

LipsyncServer *LipsyncServer::singleton = nullptr;

void LipsyncServer::_bind_methods() {

}

LipsyncServer *LipsyncServer::get_singleton() {
    return singleton;
}

LipsyncServer::LipsyncServer() {
    singleton = this;

    param_context.instantiate();
    param_context->context_id = "/lipsync";
    param_context->context_name = "Lip Syncing";
    param_context->context_description = "Lip syncing parameters";

    godot::Ref<InputParameter> voice_volume_param;
    voice_volume_param.instantiate();
    voice_volume_param->parameter_id = "/lipsync/system/voice_volume";
    voice_volume_param->parameter_name = "Voice Volume";
    voice_volume_param->parameter_description = "How loud the voice of the current microphone is.";
    param_context->add_input_parameter(voice_volume_param);

    ParameterServer* server = ParameterServer::get_singleton();
    ERR_FAIL_COND_MSG(server == nullptr, "Expected ParameterServer to be initialized.");
    server->add_parameter_context(param_context);
}

LipsyncServer::~LipsyncServer() {
    ParameterServer* server = ParameterServer::get_singleton();
    ERR_FAIL_COND_MSG(server == nullptr, "Expected ParameterServer to be initialized.");
    server->remove_parameter_context(param_context);
}