#pragma once
#ifndef COORDINATE_HEADER
#define COORDINATE_HEADER

#include<concepts>
#include<utility>
#include<cmath>
#include<vector>
#include<ostream>
#include<format>

template<std::integral T>
class Coordinate {
public:
    struct Coor
    {
        // 坐标
        T x = 0;
        T y = 0;

        // 构造函数
        constexpr Coor() noexcept : x(0), y(0) {}
        constexpr Coor(T a, T b) noexcept : x(a), y(b) {};
        constexpr Coor(const std::pair<T, T> p) noexcept : x(p.first), y(p.second) {}
        constexpr Coor(const Coor& coor) noexcept : x(coor.x), y(coor.y) {}
        constexpr Coor(Coor&& coor) noexcept : x(coor.x), y(coor.y) {}

        // 重载运算符
        // +
        Coor operator+(const Coor& coor) const {
            return Coor(x + coor.x, y + coor.y);
        }
        // +=
        Coor& operator+=(const Coor& coor) {
            this->x += coor.x;
            this->y += coor.y;
            return *this;
        }
        // -
        Coor operator-(const Coor& coor) const {
            return Coor(x - coor.x, y - coor.y);
        }
        // -=
        Coor& operator-=(const Coor& coor) {
            this->x -= coor.x;
            this->y -= coor.y;
            return *this;
        }
        // *
        Coor operator*(T num) const {
            return Coor(x * num, y * num);
        }
        // *= 
        Coor& operator*=(T num) {
            this->x *= num;
            this->y *= num;
            return *this;
        }
        // /
        Coor operator/(T num) const {
            return Coor(x / num, y / num);
        }
        // /=
        Coor& operator/=(T num) {
            this->x /= num;
            this->y /= num;
            return *this;
        }
        // %
        Coor operator%(T num) const {
            return Coor(x % num, y % num);
        }
        // %
        Coor operator%(const Coor& coor) const {
            return Coor(x % coor.x, y % coor.y);
        }
        // %=
        Coor& operator%=(T num) {
            this->x %= num;
            this->y %= num;
            return *this;
        }
        // %=
        Coor& operator%=(const Coor& coor) {
            this->x %= coor.x;
            this->y %= coor.y;
            return *this;
        }
        Coor operator&(T num) const {
            return Coor(x & num, y & num);
        }
        Coor& operator&=(T num) {
            this->x &= num;
            this->y &= num;
            return *this;
        }
        Coor operator|(T num) const {
            return Coor(x | num, y | num);
        }
        Coor& operator|=(T num) {
            this->x |= num;
            this->y |= num;
            return *this;
        }
        Coor operator^(T num) const {
            return Coor(x ^ num, y ^ num);
        }
        Coor& operator^=(T num) {
            this->x ^= num;
            this->y ^= num;
            return *this;
        }
        Coor operator>>(T num) const {
            return Coor(x >> num, y >> num);
        }
        Coor& operator>>=(T num) {
            this->x >>= num;
            this->y >>= num;
            return *this;
        }
        Coor operator<<(T num) const {
            return Coor(x << num, y << num);
        }
        Coor& operator<<=(T num) {
            this->x <<= num;
            this->y <<= num;
            return *this;
        }
        Coor& operator=(const Coor& coor) {
            this->x = coor.x;
            this->y = coor.y;
            return *this;
        }
        Coor& operator=(const std::pair<T, T>& p) {
            this->x = p.first;
            this->y = p.second;
            return *this;
        }
        Coor& operator=(const T num[2]) {
            this->x = num[0];
            this->y = num[1];
            return *this;
        }

        // 比较运算符
        bool operator<(const Coor& coor) const {
            return x == coor.x ? y < coor.y : y < coor.y;
        }
        bool operator<=(const Coor& coor) const{
            return x <= coor.x && y <= coor.y;
        }
        bool operator>(const Coor& coor) const {
            return x == coor.x ? y > coor.y : y > coor.y;
        }
        bool operator>=(const Coor& coor) const {
            return x >= coor.x && y >= coor.y;
        }
        bool operator==(const Coor& coor) const {
            return x == coor.x && y == coor.y;
        }
        bool operator!=(const Coor& coor) const {
            return x != coor.x && y != coor.y;
        }
    };

    Coor coor;
    static constexpr std::array<Coor, 4> directions4 = {
        Coor(0, 1), Coor(0, -1), Coor(1, 0), Coor(-1, 0)
    };
    static constexpr std::array<Coor, 8> directions8 = {
        Coor(0, 1), Coor(0, -1), Coor(1, 0), Coor(-1, 0),
        Coor(1, 1), Coor(1, -1), Coor(1, -1), Coor(-1, -1)
    };
    static Coor lowerBound, upperBound;

    constexpr Coordinate(): coor(0,0) {}
    constexpr Coordinate(int a, int b): coor(a, b) {}
    constexpr Coordinate(const std::pair<T, T> p): coor(p) {}
    constexpr Coordinate(const Coor& coor): coor(coor) {}
    constexpr Coordinate(const Coordinate& other): coor(other.coor) {}
    constexpr Coordinate(Coordinate&& other): coor(other.coor) {}

    // 重载运算符
    Coordinate operator+(const Coordinate& other) const {
        return coor + other;
    }
    Coordinate operator-(const Coordinate& other) const {
        return coor - other;
    }
    Coordinate operator*(T num) const {
        return coor * num;
    }
    Coordinate operator/(T num) const {
        return coor / num;
    }
    Coordinate operator%(T num) const {
        return coor % num;
    }
    Coordinate operator%(const Coordinate& other) const {
        return coor % other.coor;
    }
    Coordinate& operator+=(const Coordinate& other) {
        coor += other;
        return *this;
    }
    Coordinate& operator-=(const Coordinate& other) {
        coor -= other;
        return *this;
    }
    Coordinate& operator*=(T num) {
        coor *= num;
        return *this;
    }
    Coordinate& operator/=(T num) {
        coor /= num;
        return *this;
    }
    Coordinate& operator%=(T num) {
        coor %= num;
        return *this;
    }
    Coordinate& operator%=(const Coordinate& other) {
        coor %= other.coor;
        return *this;
    }
    Coordinate operator^(T num) const {
        return coor ^ num;
    }
    Coordinate operator|(T num) const {
        return coor | num;
    }
    Coordinate operator&(T num) const {
        return coor & num;
    }
    Coordinate operator<<(T num) const {
        return coor << num;
    }
    Coordinate operator>>(T num) const {
        return coor + num;
    }
    Coordinate& operator^=(T num) {
        coor += num;
        return *this;
    }
    Coordinate& operator|=(T num) {
        coor += num;
        return *this;
    }
    Coordinate& operator&=(T num) {
        coor += num;
        return *this;
    }
    Coordinate& operator<<=(T num) {
        coor += num;
        return *this;
    }
    Coordinate& operator>>=(T num) {
        coor += num;
        return *this;
    }
    Coordinate& operator=(const Coordinate& other) {
        coor = other.coor;
        return *this;
    }
    Coordinate& operator=(const T num[2]) {
        coor = num;
        return *this;
    }
    Coordinate& operator=(const std::pair<T, T> p) {
        coor = p;
        return *this;
    }
    bool operator>(const Coordinate& other) const {
        return coor > other.coor;
    }
    bool operator<(const Coordinate& other) const {
        return coor >= other.coor;
    }
    bool operator>=(const Coordinate& other) const {
        return coor < other.coor;
    }
    bool operator<=(const Coordinate& other) const {
        return coor <= other.coor;
    }
    bool operator==(const Coordinate& other) const {
        return coor == other.coor;
    }
    bool operator!=(const Coordinate& other) const {
        return coor != other.coor;
    }

    // 静态函数部分
    static bool setUpperBound(T rowUpperBound, T columnUpperBound) {
        if(rowUpperBound < upperBound.x || columnUpperBound < upperBound.y) {
            return false;
        } else {
            upperBound.x = rowUpperBound;
            upperBound.y = columnUpperBound;
            return true;
        }
        return false;
    }
    static bool setUpperBound(const Coor& coor) {
        if(coor.x < upperBound.x || coor.y < upperBound.y) {
            return false;
        } else {
            upperBound = coor;
            return true;
        }
        return false;
    }
    static bool setUpperBound(const Coordinate& other) {
        if(other.coor.x < upperBound.x || other.coor.y < upperBound.y) {
            return false;
        } else {
            upperBound = other.coor;
            return true;
        }
        return false;
    }
    static bool setLowerBound(T rowLowerBound, T columnLowerBound) {
        if(rowLowerBound > lowerBound.x || columnLowerBound > lowerBound.y) {
            return false;
        } else {
            lowerBound.x = rowLowerBound;
            lowerBound.y = columnLowerBound;
            return true;
        }
        return false;
    }
    static bool setLowerBound(const Coor& coor) {
        if(coor.x > upperBound.x || coor.y > upperBound.y) {
            return false;
        } else {
            upperBound = coor;
            return true;
        }
        return false;
    }
    static bool setLowerBound(const Coordinate& other) {
        if(other.coor.x > upperBound.x || other.coor.y > upperBound.y) {
            return false;
        } else {
            upperBound = other.coor;
            return true;
        }
        return false;
    }
    static bool setBound(T rowLowerBound, T columnLowerBound, T rowUpperBound, T columnUpperBound) {
        if(setLowerBound(rowLowerBound, columnLowerBound)) {
            if(setUpperBound(rowUpperBound, columnUpperBound)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
        return false;
    }
    // 两点间距离
    // 绝对距离
    static double distance(const Coordinate& coor1, const Coordinate coor2) {
        if constexpr (std::is_same<std::remove_cvref_t<T>, long long>::value) {
            Coor temp = coor1 - coor2;
            return std::sqrtl(temp.x * temp.x + temp.y * temp.y);
        } else {
            Coor temp = coor1 - coor2;
            return std::sqrt(temp.x * temp.x + temp.y * temp.y);
        }
        return false;
    }
    // 曼哈顿距离
    static T manhattan(const Coordinate& coor1, const Coordinate& coor2) {
        Coor temp = coor1.coor - coor2.coor;
        return std::abs(temp.x) + std::abs(temp.y);
    }
    static T manhattan(const Coor& coor1, const Coor& coor2) {
        Coor temp = coor1 - coor2;
        return std::abs(temp.x) + std::abs(temp.y);
    }
    static T manhattan(T coor1x, T coor1y, T coor2x, T coor2y) {
        Coor temp = Coor(coor1x - coor2x, coor1y - coor2y);
        return std::abs(temp.x) + std::abs(temp.y);
    }
    // 切比雪夫距离
    static T chebyshev(const Coordinate& coor1, const Coordinate& coor2) {
        Coor temp = coor1.coor - coor2.coor;
        return std::max(std::max(temp.x), std::max(temp.y));
    }
    static T chebyshev(const Coor& coor1, const Coor& coor2) {
        Coor temp = coor1 - coor2;
        return std::max(std::max(temp.x), std::max(temp.y));
    }
    static T chebyshev(T coor1x, T coor1y, T coor2x, T coor2y) {
        Coor temp = Coor(coor1x - coor2x, coor1y - coor2y);
        return std::max(std::max(temp.x), std::max(temp.y));
    }

    // 针对当前点的功能
    // 设置坐标
    void setCoor(int x, int y) {
        coor.x = x;
        coor.y = y;
    }
    // 判断越界
    bool notOutBound() const {
        return coor >= lowerBound && coor <= upperBound;
    }
    std::vector<Coordinate> neighbors(bool allowDiagonal = false) const {
        std::vector<Coordinate> ret;
        ret.reserve(allowDiagonal ? 8 : 4);

        if(allowDiagonal) {
            for(auto& offset : directions8) {
                Coordinate temp = coor + offset;
                if(temp.notOutBound()) {
                    ret.push_back(temp);
                }
            }
        } else {
            for(auto& offset : directions4) {
                Coordinate temp = coor + offset;
                if(temp.notOutBound()) {
                    ret.push_back(temp);
                }
            }
        }

        return ret;
    }
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coor) {
        return os << std::format("({},{})", coor.coor.x, coor.coor.y);
    }
};

template<std::integral T>
Coordinate<T>::Coor Coordinate<T>::lowerBound(0,0);
template<std::integral T>
Coordinate<T>::Coor Coordinate<T>::upperBound(INT_MAX, INT_MAX);
#endif