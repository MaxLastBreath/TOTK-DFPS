#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"
#include "nn.hpp"

typedef void (*IntervalFunc_Arg0_unk_0x28Fn)(void*, void*);

struct IntervalFunc_Arg1_unk_0x140 {
    /* 0x00 */ char unk_0x00[0x20];
    /* 0x20 */ void* window; // nvn::Window
    /* 0x28 */ char unk_0x28[0x30];
    /* 0x58 */ char unk_0x58;
    /* 0x59 */ char unk_0x59;
    /* 0x5A */ char unk_0x5A;
    /* 0x5B */ char unk_0x5B;
    /* 0x5C */
};

struct IntervalFunc_Arg0 {
    /* 0x00 */ uint32_t unk_0x00;
    /* 0x04 */ uint32_t unk_0x04;
    /* 0x08 */ float unk_0x08;
    /* 0x0C */ uint32_t unk_0x0C;
    /* 0x10 */ uint32_t unk_0x10;
    /* 0x14 */ uint32_t unk_0x14;
    /* 0x18 */ uint32_t unk_0x18;
    /* 0x1C */ uint32_t unk_0x1C;
    /* 0x20 */ uint32_t unk_0x20;
    /* 0x24 */ char unk_0x24;
    /* 0x25 */ char unk_0x25;
    /* 0x26 */ char unk_0x26;
    /* 0x27 */ char unk_0x27;
    /* 0x28 */ IntervalFunc_Arg0_unk_0x28Fn* unk_0x28;
    /* 0x2C */ uint32_t unk_0x2C;
    /* 0x30 */ struct IntervalFunc_Arg0_2* unk_0x30;
    /* 0x38 */ struct IntervalFunc_Arg0_2* unk_0x38;
    /* 0x40 */
};

struct IntervalFunc_Arg1 {
    /* 0x000 */ char unk_0x00[0x88];
    /* 0x088 */ uint32_t unk_0x88;
    /* 0x08C */ char unk_0x8C[0x8C];
    /* 0x118 */ int64_t unk_0x118;
    /* 0x120 */ char unk_0x120[0x20];
    /* 0x140 */ IntervalFunc_Arg1_unk_0x140* unk_0x140;
    /* 0x148 */
};

HOOK_DEFINE_REPLACE(GameIntervalHook) {
    static void Callback(IntervalFunc_Arg0* a0, IntervalFunc_Arg1* a1);
    static const PatchInfo CreatePatchInfo(PatchGameVersion version, uintptr_t function);
};

extern int32_t gMovieFrames;
extern float gMovieFrametime;
extern float gMovieTime;
extern bool gInMovie;

