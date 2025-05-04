#pragma once
#ifndef STLFORMATTER_HEADER
#define STLFORMATTER_HEADER

#include<format>
#include<list>
#include<vector>
#include<array>
#include<deque>
#include<stack>
#include<queue>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<utility>

namespace aleaf {
    #if __cplusplus >= 202000
    template <typename T, template <typename...> class Template>
    struct IsSpecializationOnlyTypename : std::false_type {};
    
    template <template <typename...> class Template, typename... Args>
    struct IsSpecializationOnlyTypename<Template<Args...>, Template> : std::true_type {};
    #endif
    
    #if __cplusplus < 202300
    template<typename T, template<typename, auto...> class Template>
    struct IsSpecializationOnetypename : std::false_type {};
    
    template <template <typename, auto...> class Template, typename T, auto... Ints>
    struct IsSpecializationOnetypename<Template<T, Ints...>, Template> : std::true_type {};
    #endif
    
    #if __cplusplus < 202300
    template <typename T>
    concept IsCanIterate = 
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::vector>::value ||
    IsSpecializationOnetypename<std::remove_cvref_t<T>, std::array>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::list>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::deque>::value;
    
    template<typename T>
    concept IsSet = 
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::set>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::multiset>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::unordered_set>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::unordered_multiset>::value;
    
    template<typename T>
    concept IsMap = 
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::map>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::multimap>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::unordered_map>::value ||
    IsSpecializationOnlyTypename<std::remove_cvref_t<T>, std::unordered_multimap>::value;
    #endif
    
    #if __cplusplus >= 202000
    template<typename T>
    concept IsCannotIterate = 
    IsSpecializationOnlyTypename<std::remove_cv_t<T>, std::stack>::value ||
    IsSpecializationOnlyTypename<std::remove_cv_t<T>, std::queue>::value ||
    IsSpecializationOnlyTypename<std::remove_cv_t<T>, std::priority_queue>::value;
    #endif

    template <typename Container>
    auto getFront(const Container& c) {
        if constexpr (std::is_same_v<Container, std::queue<typename Container::value_type>>) {
            return c.front();
        } else {
            return c.top();
        }
    }
}

// 声明部分
#if __cplusplus < 202300
template<aleaf::IsCanIterate T>
struct std::formatter<T>;

template<aleaf::IsMap T>
struct std::formatter<T>;

template<aleaf::IsSet T>
struct std::formatter<T>;

template<typename T, typename U>
struct std::formatter<std::pair<T, U>>;
#endif

#ifdef __cplusplus >= 202000
template<aleaf::IsCannotIterate T>
struct std::formatter<T>;
#endif

// 实现部分
#if __cplusplus < 202300
template<aleaf::IsCanIterate T>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& parseContext) {
        return parseContext.begin();
    }
    auto format(const T& t, std::format_context& context) const {
        auto out = context.out();
        out = std::format_to(out, "[");
        auto prevEnd = std::prev(t.end());
        for(auto it = t.begin(); it != t.end(); it++) {
            out = std::format_to(out, "{}", *it);
            if(it != prevEnd) {
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "]");
    }
};

template<aleaf::IsMap T>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& parseContext) {
        return parseContext.begin();
    }
    auto format(const T& t, std::format_context& context) const {
        auto out = context.out();
        out = std::format_to(out, "{{");
        auto prevEnd = std::prev(t.end());
        for(auto it = t.begin(); it != t.end(); it++) {
            out = std::format_to(out, "{}: {}", it->first, it->second);
            if(it != prevEnd) {
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "}}");
    }
};

template<aleaf::IsSet T>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& parseContext) {
        return parseContext.begin();
    }
    auto format(const T& t, std::format_context& context) const {
        auto out = context.out();
        out = std::format_to(out, "{{");
        auto prevEnd = std::prev(t.end());
        for(auto it = t.begin(); it != t.end(); it++) {
            out = std::format_to(out, "{}", *it);
            if(it != prevEnd) {
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "}}");
    }
};

template<typename T, typename U>
struct std::formatter<std::pair<T, U>> 
{
    constexpr auto parse(std::format_parse_context& parseContext) {
        return parseContext.begin();
    }
    auto format(const std::pair<T, U>& p, std::format_context& context) const {
        return std::format_to(context.out(), "({},{})", p.first, p.second);
    }
};
#endif

#ifdef __cplusplus >= 202000
template<aleaf::IsCannotIterate T>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& parseContext) {
        return parseContext.begin();
    }
    auto format(T t, std::format_context& context) const {
        auto out = context.out();
        out = std::format_to(out, "[");
        for(; t.size(); t.pop()) {
            out = std::format_to(out, "{}", aleaf::getFront(t));
            if(t.size() != 1) {
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "]");
    }
};
#endif

#endif