#pragma once

#include "base.hpp"

namespace exl::armv8::inst {

    struct AddImmediate : public impl::op100x::AddSubtractImmediate {
        
        static constexpr bool Op    = 0b0;
        static constexpr bool S     = 0b0;

        constexpr AddImmediate(reg::Register rd, reg::Register rn, u32 imm) : AddSubtractImmediate(rd.Is64(), Op, S) {
            /* static_assert(rd.Is64() == rn.Is64(), ""); */
            SetRd(rd.Index());
            SetRn(rn.Index());
            SetImm12(CalcImm(imm));
            SetSh(CalcSh(imm));
        }
    };

    static_assert(AddImmediate(reg::X0, reg::X1, 12).Value()        == 0x91003020, "");
    static_assert(AddImmediate(reg::X2, reg::X3, 46).Value()        == 0x9100B862, "");
    static_assert(AddImmediate(reg::X4, reg::X5, 0x1000).Value()    == 0x914004A4, "");
    static_assert(AddImmediate(reg::W6, reg::W7, 0x57000).Value()   == 0x11415CE6, "");
}