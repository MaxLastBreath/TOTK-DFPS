#include "PatchManager.hpp"
#include "lib.hpp"

#include "GameIntervalHook.hpp"
#include "DeviceGetProcAddressHook.hpp"
#include "UltrahandHook.hpp"
#include "MovieRenderHook.hpp"
#include "MovieMediaDataHook.hpp"
#include "GameSpeedCalcHook.hpp"

#include "main.hpp"

#define ARRAY_LENGTH(ARR) (sizeof(ARR) / sizeof((ARR)[0]))

const PatchInfo PatchManager::patches[] = {
    // Static FPS (DeviceGetProcAddress)
    DeviceGetProcAddressHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        static_cast<uintptr_t>(0x02146180)
    ),
    DeviceGetProcAddressHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        static_cast<uintptr_t>(0x021C52D0)
    ),
    DeviceGetProcAddressHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        static_cast<uintptr_t>(0x021C5180)
    ),
    DeviceGetProcAddressHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x021B9A20)
    ),
        DeviceGetProcAddressHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        static_cast<uintptr_t>(0x021b09c0)
    ),

    // Static FPS (Interval)
    GameIntervalHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        static_cast<uintptr_t>(0x008F6BEC)
    ),
    GameIntervalHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        static_cast<uintptr_t>(0x0090E904)
    ),
    GameIntervalHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        static_cast<uintptr_t>(0x0081FE84)
    ),
    GameIntervalHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x008F6670)
    ),
        GameIntervalHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        static_cast<uintptr_t>(0x008a932c)
    ),

    // Static FPS (Shrines)
    PatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        PatchType::NOP, static_cast<uintptr_t>(0x0196591C)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        PatchType::NOP, static_cast<uintptr_t>(0x019707AC)
    ),

    PatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        PatchType::NOP, static_cast<uintptr_t>(0x019BF104)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        PatchType::NOP, static_cast<uintptr_t>(0x019CA668)
    ),

    PatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        PatchType::NOP, static_cast<uintptr_t>(0x019BCC40)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        PatchType::NOP, static_cast<uintptr_t>(0x019C84D8)
    ),

    PatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        PatchType::NOP, static_cast<uintptr_t>(0x019B1F84)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        PatchType::NOP, static_cast<uintptr_t>(0x019BD9E8)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        PatchType::NOP, static_cast<uintptr_t>(0x019a2374)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        PatchType::NOP, static_cast<uintptr_t>(0x019adbe8)
    ),

#if DYNAMIC_TIMESTEP
    // Instruction NOP
    PatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        PatchType::NOP, static_cast<uintptr_t>(0x007A8414)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        PatchType::NOP, static_cast<uintptr_t>(0x00833E6C)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        PatchType::NOP, static_cast<uintptr_t>(0x00783184)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        PatchType::NOP, static_cast<uintptr_t>(0x007F7A58)
    ),
    PatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        PatchType::NOP, static_cast<uintptr_t>(0x007c9cf8)
    ),
    // Dynamic FPS
    GameSpeedCalcHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        static_cast<uintptr_t>(0x007A83E4)
    ),
    GameSpeedCalcHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        static_cast<uintptr_t>(0x00833E3C)
    ),
    GameSpeedCalcHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        static_cast<uintptr_t>(0x00783154)
    ),
    GameSpeedCalcHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x007F7A28)
    ),
        GameSpeedCalcHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        static_cast<uintptr_t>(0x007c9cc8)
    ),
#endif

    // Ultrahand
    UltrahandHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        static_cast<uintptr_t>(0x01CD3678)
    ),
    UltrahandHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        static_cast<uintptr_t>(0x01D41DFC)
    ),
    UltrahandHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        static_cast<uintptr_t>(0x01D3C82C)
    ),
    UltrahandHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x01D3675C)
    ),
    UltrahandHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        static_cast<uintptr_t>(0x01d2879c)
    ),

    // Movie Render
    MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_0_0,
        static_cast<uintptr_t>(0x0240DC78)
    ),
    MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_0,
        static_cast<uintptr_t>(0x02492068)
    ),
    MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_1,
        static_cast<uintptr_t>(0x0249ABA8)
    ),
    MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x02489658)
    ),
        MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_1_2,
        static_cast<uintptr_t>(0x02489658)
    ),
        MovieRenderHook::CreatePatchInfo(
        PatchGameVersion::VERSION_1_2_0,
        static_cast<uintptr_t>(0x0247f058)
    ),
    // Movie Media Data
    MovieMediaDataHook::CreatePatchInfo(),
};

void PatchManager::ApplyPatches(void) {
    const PatchInfo* patch = static_cast<const PatchInfo*>(nullptr);
    for (uint32_t index = 0; index < ARRAY_LENGTH(patches); index++) {
        patch = &patches[index];
        if (patch == nullptr) {
            continue;
        }

        if (patch->version != gGameVersion && patch->version != PatchGameVersion::VERSION_ANY) {
            continue;
        }

        switch (patch->type) {
            case (PatchType::DETOUR): {
                if (patch->functionSymbol != static_cast<const char*>(nullptr)) {
                    patch->InstallAtSymbol(patch->functionSymbol);
                }
                else if (patch->function != reinterpret_cast<uintptr_t>(nullptr)) {
                    patch->InstallAtOffset(patch->function);
                }
                break;
            }
            case (PatchType::NOP): {
                if (patch->function != reinterpret_cast<uintptr_t>(nullptr)) {
                    exl::patch::CodePatcher code_patcher(patch->function);
                    code_patcher.WriteInst(exl::armv8::inst::Nop());
                }
                break;
            }
            default: break;
        }

    }
}
