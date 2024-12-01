
#ifndef VDOT_CUBISM_H
#define VDOT_CUBISM_H

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

enum CubismShader {
    CUBISM_SHADER_NORM_ADD,
    CUBISM_SHADER_NORM_MIX,
    CUBISM_SHADER_NORM_MUL,
    CUBISM_SHADER_MASK,
    CUBISM_SHADER_MASK_ADD,
    CUBISM_SHADER_MASK_ADD_INV,
    CUBISM_SHADER_MASK_MIX,
    CUBISM_SHADER_MASK_MIX_INV,
    CUBISM_SHADER_MASK_MUL,
    CUBISM_SHADER_MASK_MUL_INV,
    CUBISM_SHADER_MAX
};

const static int MAX_PRINTLOG_LENGTH = 256;

const static bool DEFAULT_PROP_ANIM_LOOP = false;
const static bool DEFAULT_PROP_ANIM_LOOP_FADE_IN = true;

const static char *PROP_ANIM_GROUP = "Animation";
const static char *PROP_ANIM_EXPRESSION = "anim_expression";
const static char *PROP_ANIM_MOTION = "anim_motion";
const static char *PROP_ANIM_LOOP = "anim_loop";
const static char *PROP_ANIM_LOOP_FADE_IN = "anim_loop_fade_in";
const static char *PROP_PARAMETER_GROUP = "Parameter";
const static char *PROP_PART_OPACITY_GROUP = "PartOpacity";

const static char *SIGNAL_EFFECT_HIT_AREA_ENTERED = "hit_area_entered";
const static char *SIGNAL_EFFECT_HIT_AREA_EXITED = "hit_area_exited";

#ifdef CUBISM_MOTION_CUSTOMDATA
const static char *SIGNAL_MOTION_FINISHED = "motion_finished";
#endif // CUBISM_MOTION_CUSTOMDATA

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#endif // VDOT_CUBISM_H
