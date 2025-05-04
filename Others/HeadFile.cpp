#include<bits/stdc++.h>

namespace ranges = std::ranges;
namespace views = std::views;

/*
    g++ -std=c++20 -O2 -g -DALEAF_LOCAL -fdiagnostics-color=always -Wall -Wextra -Werror -Wshadow -Wconversion -Wsign-conversion -fsanitize=address,undefined,leak -ftrapv -D_GLIBCXX_DEBUG -o test test.cpp
*/

template<typename T>
requires(ranges::range<T> && !std::is_same_v<std::remove_cvref_t<T>, std::string>)
std::istream& operator>>(std::istream& is, T& val) {
    for(auto& it : val) {
        is >> it;
    }
    return is;
}

template<typename T>
concept enableIstream = requires(std::istream& is, T& t) {
    {is >> t} -> std::same_as<std::istream&>;
};

template<typename T>
requires(enableIstream<T>)
std::istream& input() {
    T t;
    return (std::cin >> t, t);
}

template<typename... Args>
void debug(Args... args) {
    #if __cplusplus >= 202300 && defined(ALEAF_LOCAL)
    int cnt = (cnt = 0, ((std::print("{}{}", args, (++cnt == sizeof...(args) ? '\n' : ' '))), ...), 0);
    #elif __cplusplus >= 202000 && defined(ALEAF_LOCAL)
    int cnt = (cnt = 0, ((std::cerr << std::format("{}{}", args, (++cnt == sizeof...(args) ? '\n' : ' '))), ...), 0);
    #elif defined(ALEAF_LOCAL)
    #include<OperatorOstream.hpp>
    int cnt = (cnt = 0, ((std::cerr << args << (++cnt == sizeof...(args) ? '\n' : ' ')), ...), 0);
    #endif
}

int main()
{
    #ifndef ALEAF_LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    #endif
    
    
    
    #ifdef ALEAF_LOCAL
    std::cout << std::endl;
    system("pause");
    #endif

    return 0;
}