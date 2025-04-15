#pragma once
#ifndef KMP_HEADER
#define KMP_HEADER

#include <vector>
#include <string>
#include <string_view>

namespace aleaf {
    namespace KMPType {
        struct allIndex {};
        struct firstIndex {};
    }

    std::vector<ssize_t> build_optimized_next(std::string_view pattern) {
        const size_t m = pattern.size();
        std::vector<ssize_t> next(m + 1, -1);
        ssize_t j = 0, k = -1;

        while (j < static_cast<ssize_t>(m)) {
            if (k == -1 || pattern[j] == pattern[k]) {
                ++j; ++k;
                next[j] = (j < static_cast<ssize_t>(m) && pattern[j] == pattern[k]) 
                        ? next[k] 
                        : k;
            } else {
                k = next[k];
            }
        }
        return next;
    }

    template<typename Policy>
    std::vector<size_t> KMP(std::string_view text, std::string_view pattern, size_t start = 0) {
        std::vector<size_t> matches;
        const size_t n = text.size();
        const size_t m = pattern.size();

        if (m == 0 || start > (n > m ? n - m : 0)) 
            return matches;

        const auto next = build_optimized_next(pattern);
        size_t i = start;
        ssize_t j = 0;

        while (i < n) {
            if (j == -1 || text[i] == pattern[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }

            if (j == static_cast<ssize_t>(m)) {
                matches.push_back(i - m);
                if constexpr (std::is_same_v<Policy, KMPType::firstIndex>) 
                    break;
                j = next[j];
            }
        }
        return matches;
    }
}

#endif