#pragma once
#ifndef RANDOM_HEADER
#define RANDOM_HEADER

// #include<type_traits>
#include<concepts>
#include<random>

namespace aleaf {
    template<typename T>
    struct Random;
    
    template<std::integral T>
    struct Random<T>
    {
    private:
        std::random_device rd;
        std::mt19937 gen;
        T minBound;
        T maxBound;
    
    public:
        Random() : rd(), gen(rd()) , minBound(0), maxBound(std::numeric_limits<T>().max()) {}
        Random(T _min, T _max) : rd(), gen(rd()), minBound(_min), maxBound(_max) {}
    
        T min() const {
            return this->minBound;
        }
    
        T max() const {
            return this->maxBound;
        }
    
        void min(T _min) {
            this->minBound = _min;
        }
    
        void max(T _max) {
            this->maxBound = _max;
        }
    
        T operator()() {
            return std::uniform_int_distribution<T>(minBound, maxBound)(gen);
        }
    
        T operator()(T _min, T _max) {
            return std::uniform_int_distribution<T>(_min, _max)(gen);
        }
    };
    
    template<std::floating_point T>
    struct Random<T>
    {
    private:
        std::random_device rd;
        std::mt19937 gen;
        T minBound;
        T maxBound;
    
    public:
        Random() : rd(), gen(rd()) , minBound(0), maxBound(std::numeric_limits<T>().max()) {}
        Random(T _min, T _max) : rd(), gen(rd()), minBound(_min), maxBound(_max) {}
    
        T min() const {
            return this->minBound;
        }
    
        T max() const {
            return this->maxBound;
        }
    
        void min(T _min) {
            this->minBound = _min;
        }
    
        void max(T _max) {
            this->maxBound = _max;
        }
    
        T operator()() {
            return std::uniform_real_distribution<T>(minBound, maxBound)(gen);
        }
    
        T operator()(T _min, T _max) {
            return std::uniform_real_distribution<T>(_min, _max)(gen);
        }
    };
}

#endif