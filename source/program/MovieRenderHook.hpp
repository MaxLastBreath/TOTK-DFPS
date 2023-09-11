#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"

struct MovieRender_Arg0 {
    /* 0x000 */ void* unk_0x00;
    /* 0x008 */ uint8_t unk_0x10[0x158];
    /* 0x160 */ int32_t* bufferIndex;
    /* 0x168 */ int32_t unk_0x168;
    /* 0x16C */ int32_t unk_0x16C;
};

HOOK_DEFINE_TRAMPOLINE(MovieRenderHook) {
    static bool Callback(MovieRender_Arg0* a0, void* a1); // 0x150 is the framebuffer, 0x16C is 0x00->0x1F
    static const PatchInfo CreatePatchInfo(PatchGameVersion version, uintptr_t function);
};

extern int32_t gFramesSinceLastMovieFrame;
