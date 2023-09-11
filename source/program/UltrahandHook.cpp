#include "UltrahandHook.hpp"
#include "GameSpeedCalcHook.hpp"

const float NORMAL_FRAMETIME = 1.0f / 30.0f;

float UltrahandHook::Callback(AimStruct* thisx) {
    float speed = Orig(thisx);
    float scale = gPrevGoodDeltaTime / NORMAL_FRAMETIME;
    speed *= scale;
    return speed;
}

const PatchInfo UltrahandHook::CreatePatchInfo(PatchGameVersion version, uintptr_t function) {
    return PatchInfo(version, PatchType::DETOUR, function, InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}

