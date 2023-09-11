#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

enum class PatchGameVersion : int32_t {
    VERSION_ANY = -2,
    VERSION_UNKNOWN = -1,
    VERSION_1_0_0 = 0,
    VERSION_1_1_0,
    VERSION_1_1_1,
    VERSION_1_1_2
};

enum class PatchType : int32_t {
    DETOUR,
    NOP
};

typedef void (*pfn_InstallAtOffset)(ptrdiff_t address);
typedef void (*pfn_InstallAtPtr)(uintptr_t symbol);
typedef void (*pfn_InstallAtSymbol)(const char* symbol);

struct PatchInfo {
    PatchGameVersion version = PatchGameVersion::VERSION_UNKNOWN;
    PatchType type = PatchType::DETOUR;
    uintptr_t function = reinterpret_cast<uintptr_t>(nullptr);
    const char* functionSymbol = static_cast<const char*>(nullptr);

    pfn_InstallAtOffset InstallAtOffset = nullptr;
    pfn_InstallAtPtr InstallAtPtr = nullptr;
    pfn_InstallAtSymbol InstallAtSymbol = nullptr;

    PatchInfo(PatchGameVersion version, PatchType type, uintptr_t function, pfn_InstallAtOffset installAtOffset, pfn_InstallAtPtr installAtPtr, pfn_InstallAtSymbol installAtSymbol)
        : version(version), type(type), function(function),
          InstallAtOffset(installAtOffset),
          InstallAtPtr(installAtPtr),
          InstallAtSymbol(installAtSymbol) {}
    
    PatchInfo(PatchGameVersion version, PatchType type, const char* functionSymbol, pfn_InstallAtOffset installAtOffset, pfn_InstallAtPtr installAtPtr, pfn_InstallAtSymbol installAtSymbol)
        : version(version), type(type), functionSymbol(functionSymbol),
          InstallAtOffset(installAtOffset),
          InstallAtPtr(installAtPtr),
          InstallAtSymbol(installAtSymbol) {}
    
    PatchInfo(PatchGameVersion version, PatchType type, uintptr_t function)
        : version(version), type(type), function(function) {}
};

class PatchManager {
public:
    static const PatchInfo patches[];
    static void ApplyPatches(void);
};



