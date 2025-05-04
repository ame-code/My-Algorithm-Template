#pragma once 
#ifndef CALCULATE_HEADER
#define CALCULATE_HEADER

#include<cstdint>
#include<chrono>

namespace aleaf {
    template<size_t count = 1'000'000, typename FUNC, typename... Args>
    size_t runFunction_n(const FUNC& func, const Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < count; i++) {
            func(args...);
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

#endif