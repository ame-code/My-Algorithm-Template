#pragma once 
#ifndef CALCULATE_HEADER
#define CALCULATE_HEADER

#include<cstdint>
#include<chrono>

namespace aleaf {
    template<typename Func, typename... Args>
    int64_t functionRun(Func func, Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(args...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

#endif