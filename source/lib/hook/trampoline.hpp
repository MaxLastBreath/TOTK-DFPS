#pragma once

#include "base.hpp"
#include "util/func_ptrs.hpp"
#include <functional>

#include <ro.hpp>

#define HOOK_DEFINE_TRAMPOLINE(name)                        \
struct name : public ::exl::hook::impl::TrampolineHook<name>

namespace exl::hook::impl {

    template<typename Derived>
    class TrampolineHook {
            
        template<typename T = Derived>
        using CallbackFuncPtr = decltype(&T::Callback);

        static ALWAYS_INLINE auto& OrigRef() {
            _HOOK_STATIC_CALLBACK_ASSERT();

            static constinit CallbackFuncPtr<> s_FnPtr = nullptr;

            return s_FnPtr;
        }

        public:
        template<typename... Args>
        static ALWAYS_INLINE decltype(auto) Orig(Args &&... args) {
            _HOOK_STATIC_CALLBACK_ASSERT();

            return OrigRef()(std::forward<Args>(args)...);
        }

        static ALWAYS_INLINE void InstallAtOffset(ptrdiff_t address) {
            _HOOK_STATIC_CALLBACK_ASSERT();

            OrigRef() = hook::Hook(util::modules::GetTargetStart() + address, Derived::Callback, true);
        }

        template<typename R, typename ...A>
        static ALWAYS_INLINE void InstallAtFuncPtr(util::GenericFuncPtr<R, A...> ptr) {
            _HOOK_STATIC_CALLBACK_ASSERT();
            using ArgFuncPtr = decltype(ptr);

            static_assert(std::is_same_v<ArgFuncPtr, CallbackFuncPtr<>>, "Argument pointer type must match callback type!");

            OrigRef() = hook::Hook(ptr, Derived::Callback, true);
        }

        static ALWAYS_INLINE void InstallAtPtr(uintptr_t ptr) {
            _HOOK_STATIC_CALLBACK_ASSERT();
            
            OrigRef() = hook::Hook(ptr, Derived::Callback, true);
        }

        static ALWAYS_INLINE void InstallAtSymbol(const char* sym) {
            _HOOK_STATIC_CALLBACK_ASSERT();

            uintptr_t address = 0;
            EXL_ASSERT(nn::ro::LookupSymbol(&address, sym).isSuccess(), "Unable to Find Address for Symbol! %s", sym);

            OrigRef() = hook::Hook(address, Derived::Callback, true);
        }
    };

}
