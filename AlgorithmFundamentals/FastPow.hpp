#pragma once
#ifndef FASTPOW_HEADER
#define FASTPOW_HEADER

#include <concepts>

// ========================
// 快速幂
// 最后修改日期：2025-04-15
// ========================

namespace aleaf {
    // 循环实现
    template<std::integral INT = int>
    INT fastPow(INT base, INT index) {
        INT ret = 1;
        for (; index; index >>= 1, base *= base) {
            if (index & 1) ret *= base;
        }
        return ret;
    }

    // 带模运算的循环实现
    template<std::integral INT = int>
    INT fastPow(INT base, INT index, INT mod) {
        INT ret = 1;
        base %= mod; // 防止溢出
        for (; index; index >>= 1, base = base * base % mod) {
            if (index & 1) ret = ret * base % mod;
        }
        return ret;
    }
}

#endif