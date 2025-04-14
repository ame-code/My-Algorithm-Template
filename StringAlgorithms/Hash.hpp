#pragma once
#ifndef HASH_HEADER
#define HASH_HEADER

#include <array>
#include <vector>
#include <string>
#include <utility>
#include <ranges>

enum class HashType{array, vector};

template<HashType hashtype>
class Hash;

template<>
class Hash<HashType::array> {
private:
    constexpr static size_t powArraySize = 10'000;
    constexpr static size_t baseFisrt = 131;
    constexpr static size_t baseSecond = 233;
    constexpr static auto calPowArray = [](size_t baseFirst, size_t baseSecond) constexpr -> std::array<std::pair<size_t, size_t>, powArraySize + 1> {
        std::array<std::pair<size_t, size_t>, powArraySize + 1> arr{};
        arr[0] = std::pair<size_t, size_t>(1ULL, 1ULL);
        for(size_t i : std::views::iota(1ULL, powArraySize + 1)) {
            arr[i].first = arr[i - 1].first * baseFirst;
            arr[i].second = arr[i - 1].second * baseSecond;
        }
        return arr;
    };
    constexpr static std::array<std::pair<size_t, size_t>, powArraySize + 1> powValue = calPowArray(baseFisrt, baseSecond);
    std::vector<std::pair<size_t, size_t>> hashValue;
    
public:
    constexpr Hash(): hashValue(0) {}
    constexpr Hash(size_t size): hashValue(size + 1, std::pair<size_t, size_t>(0ULL, 0ULL)) {}
    Hash(const std::string& str) {
        calcuteHash(str);
    }
    constexpr Hash(Hash& hash): hashValue(hash.hashValue) {}

    void calcuteHash(const std::string str) {
        size_t len = str.length();
        hashValue.assign(len + 1, std::pair<size_t, size_t>(0ULL, 0ULL));
        for(size_t i : std::views::iota(0ULL, len)) {
            hashValue[i + 1].first = hashValue[i].first * baseFisrt + str[i];
            hashValue[i + 1].second = hashValue[i].second * baseSecond + str[i];
        }
    }

    std::pair<size_t, size_t> get(size_t startPos = 0, size_t size = ULONG_LONG_MAX) {
        size = std::min(size, hashValue.size() - 1);
        size_t l = startPos + 1;
        size_t r = l + size - 1;
        return std::make_pair(hashValue[r].first - hashValue[l - 1].first * powValue[r - l + 1].first, hashValue[r].second - hashValue[l - 1].second * powValue[r - l + 1].second);
    }
};

template<>
class Hash<HashType::vector> {
private:
    constexpr static size_t baseFisrt = 131;
    constexpr static size_t baseSecond = 233;
    std::vector<std::pair<size_t, size_t>> hashValue;
    std::vector<std::pair<size_t, size_t>> powValue;
    
public:
    constexpr Hash(): hashValue(0), powValue(1, std::pair<size_t, size_t>(1ULL, 1ULL)) {}
    constexpr Hash(size_t size): hashValue(size + 1, std::pair<size_t, size_t>(0ULL, 0ULL)), powValue(1, std::pair<size_t, size_t>(1ULL, 1ULL)) {}
    Hash(const std::string& str): powValue(1, std::pair<size_t, size_t>(1ULL, 1ULL)){
        calcuteHash(str);
    }
    constexpr Hash(Hash& hash): hashValue(hash.hashValue), powValue(hash.powValue) {}

    void calcuteHash(const std::string str) {
        size_t len = str.length();
        hashValue.assign(len + 1, std::pair<size_t, size_t>(0ULL, 0ULL));
        if(len + 1 > powValue.size()) {
            size_t n = powValue.size();
            powValue.resize(len + 1);
            for(size_t i : std::views::iota(n, len + 1)) {
                powValue[i].first = powValue[i - 1].first * baseFisrt;
                powValue[i].second = powValue[i - 1].second * baseSecond;
            }
        }
        for(size_t i : std::views::iota(0ULL, len)) {
            hashValue[i + 1].first = hashValue[i].first * baseFisrt + str[i];
            hashValue[i + 1].second = hashValue[i].second * baseSecond + str[i];
        }
    }

    std::pair<size_t, size_t> get(size_t startPos = 0, size_t size = ULONG_LONG_MAX) {
        size = std::min(size, hashValue.size() - 1);
        size_t l = startPos + 1;
        size_t r = l + size - 1;
        return std::make_pair(hashValue[r].first - hashValue[l - 1].first * powValue[r - l + 1].first, hashValue[r].second - hashValue[l - 1].second * powValue[r - l + 1].second);
    }
};

#endif