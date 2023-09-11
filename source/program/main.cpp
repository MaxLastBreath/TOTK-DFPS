#include "lib.hpp"
#include "nn/oe.hpp"
#include "PatchManager.hpp"
#include "main.hpp"

const char GAME_VERSION_1_0_0[] = "1.0.0";
const char GAME_VERSION_1_1_0[] = "1.1.0";
const char GAME_VERSION_1_1_1[] = "1.1.1";
const char GAME_VERSION_1_1_2[] = "1.1.2";
const char GAME_VERSION_1_2_0[] = "1.2.0";

const float ABORT_FRAMETIME = 1.0f;
const float NORMAL_FRAMETIME = (1.0f / 30.0f);
const float UNSTABLE_FRAMETIME = (1.0f / 20.0f);

PatchGameVersion gGameVersion = PatchGameVersion::VERSION_UNKNOWN;

extern "C" PatchGameVersion GetGameVersion(const char* version) {
    if (strncmp(version, GAME_VERSION_1_0_0, 16) == 0) {
        return PatchGameVersion::VERSION_1_0_0;
    }
    else if (strncmp(version, GAME_VERSION_1_1_0, 16) == 0) {
        return PatchGameVersion::VERSION_1_1_0;
    }
    else if (strncmp(version, GAME_VERSION_1_1_1, 16) == 0) {
        return PatchGameVersion::VERSION_1_1_1;
    }
    else if (strncmp(version, GAME_VERSION_1_1_2, 16) == 0) {
        return PatchGameVersion::VERSION_1_1_2;
    }
    else if (strncmp(version, GAME_VERSION_1_2_0, 16) == 0) {
        return PatchGameVersion::VERSION_1_2_0;
    }
    
    return PatchGameVersion::VERSION_UNKNOWN;
}

extern "C" void exl_main(void* x0, void* x1) {
    nn::oe::DisplayVersion displayVersion;

    exl::hook::Initialize();

    nn::oe::GetDisplayVersion(&displayVersion);
    gGameVersion = GetGameVersion(displayVersion.name);

    PatchManager::ApplyPatches();
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
