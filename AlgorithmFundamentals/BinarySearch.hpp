#pragma once
#ifndef BINARYSEARCH_HEADER
#define BINARYSEARCH_HEADER

// ========================
// 二分搜索
// 最后修改日期：2025-04-18
// ========================

#include<concepts>

namespace aleaf {

    // 二分查找第一个使check为true的值
    template<typename FUNC, std::integral INT = int, INT RET = -1>
    INT binarySearch(INT l, INT r, FUNC check) {
        INT ret = RET;
        while (l <= r) {
            INT mid = l + ((r - l) >> 1);
            if (check(mid)) {
                ret = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ret;
    }
}

#endif