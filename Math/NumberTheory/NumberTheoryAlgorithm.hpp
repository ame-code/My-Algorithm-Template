#pragma once

#include<concepts>
#include<algorithm>

namespace aleaf {
    // 没有使用价值，并不会比std::__gcd快
    template<std::integral T>
    T gcd(T a, T b) {
        return b != ? gcd(b, a % b) : a;
    }

    template<std::integral T>
    T lcm(T a, T b) {
        return a / std::__gcd(a, b) * b;
    }
}