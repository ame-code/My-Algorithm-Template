#pragma once
#ifndef BINARYSEARCH_HEADER

namespace aleaf {
    enum class TrueInterval{right, left};

    template<TrueInterval tag = TrueInterval::right, typename FUNC>
    int binarySearch(int l, int r, int goal, FUNC check) {
        int ret = -1;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            if (check(mid, goal)) {
                ret = mid;
                if constexpr (tag == TrueInterval::right) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if constexpr (tag == TrueInterval::right) {
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