#include<bits/stdc++.h>
// using namespace std;
namespace aleaf {
    template<typename T>
    void setMin(T &a, T &b) {
        b = a = (a < b ? a : b);
    }

    template<typename T>
    void setMax(T &a, T &b) {
        b = a = (a > b ? a : b);
    }
    template<typename T>
    T& min(T& a, T& b) {
        return a < b ? a : b;
    }

    template<typename T>
    T& max(T& a, T& b) {
        return a > b ? a : b;
    }

    template<std::integral T>
    T abs(const T &a) {
        return (a ^ (~(a >> 31) + 1) + (a >> 31));
    }

    template<typename T, typename... Args>
    auto makeVector(size_t n, Args... args) {
        if constexpr (sizeof...(args) == 1) {
            return std::vector<T>(n, args...);
        } else {
            return std::vector<T>(n, makeVector<T>(args...));
        }
    }
    
    template<typename T, typename... Args>
    auto makeArray(size_t n, Args... args) {
        if constexpr (sizeof...(args) == 1) {
            return std::array<T, n>();
        } else {
            return std::array<makeArray<T>, n>();
        }
    }

    // 没啥可读性版 :)
    bool LeapYear(int year) {
        return year % 4 == 0 && (year % 400 == 0 || !(year % 400 !=0 && year % 100 == 0));
    }
};