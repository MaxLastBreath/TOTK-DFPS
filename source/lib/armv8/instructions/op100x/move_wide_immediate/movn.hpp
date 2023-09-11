#pragma once

#include "base.hpp"

namespace exl::armv8::inst {

    struct Movn : public impl::op100x::MoveWideImmediate {
        
        static constexpr u8 Opc = 0b00;
        static constexpr u8 Hw = 0b00;

        constexpr Movn(reg::Register reg, u16 imm) : MoveWideImmediate(reg, Opc, Hw, imm) {}

    };
}