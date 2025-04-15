#pragma once
#ifndef BINARYSEARCH_HEADER
#define BINARYSEARCH_HEADER

// ========================
// 二分搜索
// 最后修改日期：2025-04-15
// ========================

#include<concepts>

namespace aleaf {
    enum class TrueBinaryInterval{right, left};

    template<TrueBinaryInterval tag, std::integral INT = int, typename FUNC>
    INT binarySearch(INT l, INT r, INT goal, FUNC check) {
        INT ret = -1;
        while (l <= r) {
            INT mid = l + ((r - l) >> 1);
            if (check(mid, goal)) {
                ret = mid;
                if constexpr (tag == TrueBinaryInterval::right) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if constexpr (tag == TrueBinaryInterval::right) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return ret;
    }
}

#endif