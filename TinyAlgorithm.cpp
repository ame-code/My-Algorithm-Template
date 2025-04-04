#include<concepts>
namespace TinyAlgorithm {
    template<std::integral T>
    void swap(T& a,T& b) {
        a ^= b ^= a ^= b;
    }

    template<typename T>
    void setMin(T &a, T &b) {
        a = a < b ? a : b;
        b = a;
    }

    template<typename T>
    void setMax(T &a, T &b) {
        a = a > b ? a : b;
        b = a;
    }
}