#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"

struct GameTimeStruct {
    /* 0x00 */ uint8_t unk_0x00[0x8];
    /* 0x08 */ float GameSpeed_8;
    /* 0x0C */ float DeltaTime_C;
    /* 0x10 */
};

HOOK_DEFINE_TRAMPOLINE(GameSpeedCalcHook) {
    static void Callback(GameTimeStruct* a1, int32_t presentInterval);
    static const PatchInfo CreatePatchInfo(PatchGameVersion version, uintptr_t function);
};

extern float gPrevDeltaTime;
extern float gPrevGoodDeltaTime;
