#include "MovieRenderHook.hpp"

int32_t gFramesSinceLastMovieFrame = -1;

bool MovieRenderHook::Callback(MovieRender_Arg0* a0, void* a1) {
    gFramesSinceLastMovieFrame = 0;
    return Orig(a0, a1);
}

const PatchInfo MovieRenderHook::CreatePatchInfo(PatchGameVersion version, uintptr_t function) {
    return PatchInfo(version, PatchType::DETOUR, function, InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}

