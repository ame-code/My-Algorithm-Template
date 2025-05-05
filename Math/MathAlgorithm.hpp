#pragma once
#ifndef MATHALGORITHM_HEADER
#define MATHALGORITHM_HEADER

#include<cmath>

namespace aleaf {
    template<std::integral T>
    T sqrt(T n) {
        double approx = std::sqrt(n);
        T floor_val = static_cast<T>(approx);

        while((floor_val + 1) * (floor_val + 1) <= n) ++floor_val;
        while(floor_val * floor_val > n) --floor_val;

        return floor_val;
    }
}

#endif