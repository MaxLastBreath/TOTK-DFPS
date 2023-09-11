#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"

HOOK_DEFINE_TRAMPOLINE(MovieMediaDataHook) {
    static bool Callback(void* thisx, const char* name, int32_t* value);
    static const PatchInfo CreatePatchInfo(void);
};

extern int32_t gMovieFramerate;

