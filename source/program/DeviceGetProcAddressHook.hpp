#pragma once

#include "types.h"
#include "lib.hpp"
#include "PatchManager.hpp"

typedef void (*pfn_nvnWindowSetPresentInterval)(void* window, int interval);
typedef void* (*pfn_DeviceGetProcAddress)(void* device, const char* proc);

HOOK_DEFINE_TRAMPOLINE(DeviceGetProcAddressHook) {
    static void Callback(void* device, pfn_DeviceGetProcAddress DeviceGetProcAddress);
    static const PatchInfo CreatePatchInfo(PatchGameVersion version, uintptr_t function);
};

extern pfn_nvnWindowSetPresentInterval gNvnWindowSetPresentInterval;
