#pragma once

#include "common.hpp"

#define EXL_MODULE_NAME "exlaunch"
#define EXL_MODULE_NAME_LEN 8

#define EXL_DEBUG
#define EXL_USE_FAKEHEAP

/*
#define EXL_SUPPORTS_REBOOTPAYLOAD
*/

namespace exl::setting {
    /* How large the fake .bss heap will be. */
    constexpr size_t HeapSize = 0x10000;

    /* How large the JIT area will be for hooks. */
    constexpr size_t JitSize = 0x1000;

    /* How large the area will be inline hook pool. */
    constexpr size_t InlinePoolSize = 0x1000;

    /* Sanity checks. */
    static_assert(ALIGN_UP(JitSize, PAGE_SIZE) == JitSize, "");
    static_assert(ALIGN_UP(InlinePoolSize, PAGE_SIZE) == JitSize, "");
}