#include<bits/stdc++.h>
// using namespace std;
namespace aleaf {
    auto& min(auto&& a) {
        return a;
    }
    
    auto& max(auto&& a) {
        return a;
    }
    
    auto& min(auto&& a, auto&& b, auto&&... args) {
        return a < b ? min(a, args...) : min(b, args...);
    }
    
    auto& max(auto&& a, auto&& b, auto&&... args) {
        return a > b ? max(a, args...) : max(b, args...);
    }
    
    auto& setMin(auto&& a) {
        return a;
    }
    
    auto& setMax(auto&& a) {
        return a;
    }
    
    auto& setMin(auto&& a, auto&& b, auto&&... args) {
        return a < b ? b = setMin(a, args...) : a = setMin(b, args...);
    }
    
    auto& setMax(auto&& a, auto&& b, auto&&... args) {
        return a > b ? b = setMax(a, args...) : a = setMax(b, args...);
    }

    auto abs(const auto& a) {
        return (a ^ (~(a >> 31) + 1) + (a >> 31));
    }

    template<std::integral T>
    void swap(T& a, T& b) {
        a ^= b ^= a ^= b;
    }
    
    template<typename T, typename... Args>
    auto vector(size_t n, Args... args) {
        static_assert(sizeof...(args) >= 1);
        if constexpr (sizeof...(args) == 1) {
            return std::vector<T>(n, args...);
        } else {
            return std::vector(n, vector<T>(args...));
        }
    }
    
    // 没啥可读性版 :)
    bool LeapYear(int year) {
        return year % 4 == 0 && (year % 400 == 0 || !(year % 400 !=0 && year % 100 == 0));
    }
};