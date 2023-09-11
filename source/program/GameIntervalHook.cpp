#include "GameIntervalHook.hpp"
#include "DeviceGetProcAddressHook.hpp"
#include "MovieMediaDataHook.hpp"
#include "MovieRenderHook.hpp"
#include "main.hpp"

int32_t sTargetInterval = PRESENT_INTERVAL;
int32_t gMovieFrames = -1;
float gMovieFrametime = NORMAL_FRAMETIME;
float gMovieTime = 0.0f;
bool gInMovie = false;

void GameIntervalHook::Callback(IntervalFunc_Arg0* a0, IntervalFunc_Arg1* a1) {
    int32_t interval = sTargetInterval;

    if (gFramesSinceLastMovieFrame != -1) {
        if (gFramesSinceLastMovieFrame == 0) {
            interval = 60 / gMovieFramerate;
            gMovieFrametime = 1.0f / (float)gMovieFramerate;
            gInMovie = true;
        }

        gFramesSinceLastMovieFrame++;
        if (gFramesSinceLastMovieFrame > 16) {
            gFramesSinceLastMovieFrame = -1;
            gMovieFrames = -1;
            gMovieTime = 0.0f;
            gInMovie = false;
        }
    }

    if (a0 == nullptr || a1 == nullptr) {
        return;
    }

    // game runs at the incorrect speed if we don't do this
#if DYNAMIC_TIMESTEP==0
    a0->unk_0x14 = interval;
    a0->unk_0x18 = interval;
#else
    a0->unk_0x14 = GAME_UPDATE_INTERVAL;
    a0->unk_0x18 = GAME_UPDATE_INTERVAL;
#endif
    a0->unk_0x1C = 0;

    if (a1->unk_0x140 == nullptr) {
        return;
    }

    if (a1->unk_0x140->window == nullptr) {
        return;
    }

    if (gNvnWindowSetPresentInterval != nullptr) {
        gNvnWindowSetPresentInterval(a1->unk_0x140->window, interval);
    }
}

const PatchInfo GameIntervalHook::CreatePatchInfo(PatchGameVersion version, uintptr_t function) {
    return PatchInfo(version, PatchType::DETOUR, function, InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}


