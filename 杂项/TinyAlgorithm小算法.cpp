#include<concepts>
// using namespace std;
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

    template<std::integral T>
    void OppositeNumber(T &a) {
        a = ~a + 1;
    }

    template<std::integral T>
    T&& abs(const T &a) {
        return move(a^(~(a>>31)+1)+(a>>31));
    }
};