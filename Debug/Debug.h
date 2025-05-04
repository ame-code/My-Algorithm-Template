#pragma once
#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include"STLFormatter.hpp"
#include"OperatorOstream.hpp"

namespace aleaf {
    template<typename... Args>
    void debug(Args... args) {
        #if __cplusplus >= 202300 && defined(ALEAF_LOCAL)
        int cnt = (cnt = 0, ((std::print("{}{}", args, (++cnt == sizeof...(args) ? '\n' : ' '))), ...), 0);
        #elif __cplusplus >= 202000 && defined(ALEAF_LOCAL)
        int cnt = (cnt = 0, ((std::cerr << std::format("{}{}", args, (++cnt == sizeof...(args) ? '\n' : ' '))), ...), 0);
        #elif defined(ALEAF_LOCAL)
        int cnt = (cnt = 0, ((std::cerr << args << (++cnt == sizeof...(args) ? '\n' : ' ')), ...), 0);
        #endif
    }
}

#endif