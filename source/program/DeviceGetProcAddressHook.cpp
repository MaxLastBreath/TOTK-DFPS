#include "DeviceGetProcAddressHook.hpp"

pfn_nvnWindowSetPresentInterval gNvnWindowSetPresentInterval = nullptr;

void DeviceGetProcAddressHook::Callback(void* device, pfn_DeviceGetProcAddress DeviceGetProcAddress) {
    Orig(device, DeviceGetProcAddress);
    gNvnWindowSetPresentInterval = (pfn_nvnWindowSetPresentInterval)DeviceGetProcAddress(device, "nvnWindowSetPresentInterval");
}

const PatchInfo DeviceGetProcAddressHook::CreatePatchInfo(PatchGameVersion version, uintptr_t function) {
    return PatchInfo(version, PatchType::DETOUR, function, InstallAtOffset, InstallAtPtr, InstallAtSymbol);
}

