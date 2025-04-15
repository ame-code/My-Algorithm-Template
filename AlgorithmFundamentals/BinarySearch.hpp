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

    template<TrueBinaryInterval tag, std::integral Int = int, typename FUNC>
    Int binarySearch(Int l, Int r, Int goal, FUNC check) {
        Int ret = -1;
        while (l <= r) {
            Int mid = l + ((r - l) >> 1);
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