#pragma once
#ifndef OPERATOROSTREAM_HEADER
#define OPERATOROSTREAM_HEADER

// ========================
// 重载输出流
// 最后修改时间：2025-04-22
// ========================

#include<bits/stdc++.h>

// 重载输出流声明部分
// array数组输出
template<typename T, size_t n>
std::ostream& operator<<(std::ostream& os, std::array<T, n> arr);
// vector数组输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec);
// pair数对输出
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> p);
// stack栈输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> s);
// queue队列输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::queue<T> q);
// deque双端队列输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> dq);
// priority_queue优先队列输出
template<typename... args>
std::ostream& operator<<(std::ostream& os, std::priority_queue<args...> pq);
// map映射输出
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::map<T1, T2> mp);
// set集合输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> st);
// debug多种变量输出
template<typename T, typename... Args>
void debug(T first, Args... args);
// 重载输出流声明部分



// 重载输出流实现部分
// array数组输出
template<typename T, size_t n>
std::ostream& operator<<(std::ostream& os, std::array<T, n> arr) {
    for(size_t i = (os << '{', 0); i < n; i++, os << (",}"[i == n])) {
        os << arr[i];
    }
    return os;
}

// vector数组输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
    for(size_t i = (os << '{', 0); i < vec.size(); i++, os << (",}"[i == vec.size()])) {
        os << vec[i];
    }
    return os;
}

// pair数对输出
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> p) {
    os << std::format("({0},{1})", p.first, p.second);
    return os;
}

// stack栈输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> s) {
    for(os << '{'; !s.empty(); s.pop(),os << (",}"[s.empty()]))
        os << s.top();
    return os;
}

// queue队列输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    for(os << '{'; !q.empty(); q.pop(),os << (",}"[q.empty()]))
        os << q.front();
    return os;
}

// deque双端队列输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> dq) {
    for(os << '{'; !dq.empty(); dq.pop_front(),os << (",}"[dq.empty()]))
        os << dq.front();
    return os;
}

// priority_queue优先队列输出
template<typename... args>
std::ostream& operator<<(std::ostream& os, std::priority_queue<args...> pq) {
    for(os << '{'; !pq.empty(); pq.pop(), os << (",}"[pq.empty()]))
        os << pq.top();
    return os;
}

// map映射输出
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::map<T1, T2> mp) {
    for(auto it = (os << '{', mp.begin()); it != mp.end(); it++, os << (",}"[it == mp.end()])) {
        os << std::format("[{0} -> {1}]", it->first, it->second);
    }
    return os;
}

// set集合输出
template<typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> st) {
    for(auto it = (os << '{', st.begin()); it != st.end(); it++, os << (",}"[it == st.end()])) {
        os << *it;
    }
    return os;
}

// debug多种变量输出
void debug() {
    std::cerr << "Debug Args Empty\n";
}

template<typename T, typename... Args>
void debug(T first, Args... args) {
    std::cerr << first << ' ';
    debug(args...);
}

#endif