#include "GameSpeedCalcHook.hpp"
#include "GameIntervalHook.hpp"
#include "main.hpp"

#include "nn/os/os_tick.hpp"
#include "nn/os/os_thread_api.hpp"

nn::os::Tick sPrevTick;
bool sFirstTick;

float gPrevDeltaTime = NORMAL_FRAMETIME;
float gPrevGoodDeltaTime = NORMAL_FRAMETIME;
int32_t sUnstableFrames = 0;

void GameSpeedCalcHook::Callback(GameTimeStruct* a1, int32_t presentInterval) {
    float deltaTime;

    // Handle first tick case
    if (sFirstTick) {
        sFirstTick = false;
        sPrevTick = nn::os::GetSystemTick();
        Orig(a1, presentInterval);
        return;
    }

    // Ideally this should only be called once and then cached, but seems the first few calls can give a bad result?
    s64 tickFrequency = nn::os::GetSystemTickFrequency();
    nn::os::Tick curTick = nn::os::GetSystemTick();
    s64 difference = curTick.GetInt64Value() - sPrevTick.GetInt64Value();
    sPrevTick = curTick;
    
    // prevent divide by zero error
    if (tickFrequency == 0) {
        tickFrequency = 1;
    }

    deltaTime = float(difference) / float(tickFrequency);
    if (gInMovie) {
        gMovieTime += deltaTime;
        gMovieFrames = gMovieTime / gMovieFrametime;
        double nextFrameTime = (gMovieFrames + 1) * gMovieFrametime;
        double diff = nextFrameTime - gMovieTime;

        if (diff > 0) {
            nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(static_cast<int64_t>(diff * 1e9)));
        }

        a1->GameSpeed_8 = (gMovieFrametime * 30.0);
        a1->DeltaTime_C = gMovieFrametime;
        Orig(a1, presentInterval);
        return;
    }


    // If we've got seriously bad FPS, there's nothing that we can do
    if (deltaTime >= ABORT_FRAMETIME) {
        a1->GameSpeed_8 = (NORMAL_FRAMETIME * 30.0f);
        a1->DeltaTime_C = NORMAL_FRAMETIME; 
        Orig(a1, presentInterval);
        return;
    }

    bool hitch = deltaTime > gPrevDeltaTime * 1.4f;
    bool unstable = deltaTime >= UNSTABLE_FRAMETIME;
    if (unstable || hitch) {
        sUnstableFrames++;
        if ((unstable && !hitch) || sUnstableFrames > presentInterval + 1) {
            deltaTime = UNSTABLE_FRAMETIME; // If we didn't hitch, and are unstable, or we have been unstable for the average frames, give up and use 1.0 / 20.0
        }
        else {
            deltaTime = gPrevGoodDeltaTime; // this deltatime is unusable, so we will use the last one to look slightly smoother than 20fps
        }
    }
    else {
        sUnstableFrames = 0;
    }

    if (!unstable && !hitch) {
        gPrevGoodDeltaTime = deltaTime;
    }
    gPrevDeltaTime = deltaTime;

    a1->GameSpeed_8 = (deltaTime * 30.0f);
    a1->DeltaTime_C = deltaTime; 
    
    Orig(a1, presentInterval);
}

const PatchInfo GameSpeedCalcHook::CreatePatchInfo(PatchGameVersion version, uintptr_t function) {
    return PatchInfo(version, PatchType::DETOUR, function, InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}

