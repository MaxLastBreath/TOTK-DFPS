#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"

struct AimStruct_100 {
    uint8_t unk_0x00[0xC2C];
    float AimSpeedY;
};

struct AimStruct_11X {
    uint8_t unk_0x00[0xC54];
    float AimSpeedY;
};

union AimStruct {
    AimStruct_100 VERSION_1_0_0;
    AimStruct_11X VERSION_1_1_X;
    AimStruct_12X VERSION_1_2_X;
};

HOOK_DEFINE_TRAMPOLINE(UltrahandHook) {
    static float Callback(AimStruct* thisx);
    static const PatchInfo CreatePatchInfo(PatchGameVersion version, uintptr_t function);
};

