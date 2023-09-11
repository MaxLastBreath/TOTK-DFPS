#include "MovieMediaDataHook.hpp"

int32_t gMovieFramerate = 30;

// FindInt32
bool MovieMediaDataHook::Callback(void* thisx, const char* name, int32_t* value) {
    int framerate = 30;

    if (thisx != nullptr) {
        if (Orig(thisx, "frame-rate", &framerate)) {
            gMovieFramerate = framerate;
        }

        return Orig(thisx, name, value);
    }

    return false;
}

const PatchInfo MovieMediaDataHook::CreatePatchInfo(void) {
    return PatchInfo(PatchGameVersion::VERSION_ANY, PatchType::DETOUR, "_ZNK5movie9MediaData9FindInt32EPKcPi", InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}

