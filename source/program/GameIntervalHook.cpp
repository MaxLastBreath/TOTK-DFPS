#include "GameIntervalHook.hpp"
#include "DeviceGetProcAddressHook.hpp"
#include "MovieMediaDataHook.hpp"
#include "MovieRenderHook.hpp"
#include "main.hpp"
#include "nn/fs.hpp"
#include "logger.hpp"
#include "lib/simpleini-4.20/SimpleIni.h"

// sTargetInterval is the interval of FPS target, 1 = 60, 2 = 30, 3 = 20
int32_t frame = 1;
int32_t gMovieFrames = -1;
float gMovieFrametime = NORMAL_FRAMETIME;
float gMovieTime = 0.0f;
bool gInMovie = false;
bool idk = true;

void FPS_Interval() {
    /* Mount ROM */
    nn::fs::MountRom("content");
    nn::fs::MountSdCard("sd");

    const char* iniFilePath = "content:/dfps/default.ini";
    nn::fs::FileHandle input_handle = {};

    // Open the INI file for reading
    nn::Result openResult = nn::fs::OpenFile(std::addressof(input_handle), iniFilePath, nn::fs::OpenMode_Read);

    if (!openResult.isSuccess()) {
        OutputDebug("sd:/DFPS++_DEBUG.txt", "Error Opening the file.", true);
        return;
    }

    long int file_size = 0;
    nn::Result sizeResult = nn::fs::GetFileSize(std::addressof(file_size), input_handle);

    if (!sizeResult.isSuccess()) {
        OutputDebug("sd:/DFPS++_DEBUG.txt", "Error Getting the file.", true);
        return;
    }

    // Allocate a buffer based on the file size
    char* buffer = new char[file_size];
    nn::Result readResult = nn::fs::ReadFile(input_handle, 0, buffer, file_size);

    if (!readResult.isSuccess()) {
        OutputDebug("sd:/DFPS++_DEBUG.txt", "Error reading the file.", true);
        return;
    }

    CSimpleIniA ini;
    std::string iniContent(buffer, file_size);
    const char* iniContentCStr = iniContent.c_str();
    // Convert the buffer to a string (INI content)

    if (!ini.LoadData(iniContentCStr)) {
        OutputDebug("sd:/DFPS++_DEBUG.txt", "FAILED TO READ INI FILE.", true);
        OutputDebug("sd:/DFPS++_DEBUG.txt", "INPUT INI:", true);
        OutputDebug("sd:/DFPS++_DEBUG.txt", iniContentCStr, true);
    }
    const char* maxFramerate = ini.GetValue("dFPS", "MaxFramerate", "-1");

    OutputDebug("sd:/DFPS++_DEBUG.txt", "FPS VALUE:", false);
    OutputDebug("sd:/DFPS++_DEBUG.txt", maxFramerate, true);

    int maxFramerateValue = std::stoi(maxFramerate);
    if (maxFramerateValue > 0) {
        // The MaxFramerate value was found
        if (maxFramerateValue == 60) {
            frame = 1;
        }
        else if (maxFramerateValue == 30) {
            frame = 2;
        }
        else if (maxFramerateValue == 20) {
            frame = 3;
        }
        else {
            OutputDebug("sd:/DFPS++_DEBUG.txt", "Max DFPS++.ini, Bad Value.", true);
            frame = 1; // Default value if not found
        }
    }
    // Free the allocated buffer
    delete[] buffer;
    nn::fs::CloseFile(input_handle);
    return;
}

void GameIntervalHook::Callback(IntervalFunc_Arg0* a0, IntervalFunc_Arg1* a1) {

    if (idk == true) {
        idk = false;
        FPS_Interval();
    }

    int32_t interval = frame;


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


