#include<bits/stdc++.h>
template<std::integral T = int>
class Coordinate {
public:
    using Integer = T;

    // 坐标
    Integer x = 0;
    Integer y = 0;
    // 网格边界
    static Integer xAxisLowBound, xAxisUpBound, yAxisLowBound, yAxisUpBound;
    // 静态方向向量(4方向)
    inline static constexpr std::array<Coordinate<Integer>, 4> directions4 = {
        Coordinate{0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };
    inline static constexpr std::array<Coordinate<Integer>, 8> directions8 = {
        Coordinate{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
        {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };

    // 构造函数
    Coordinate() : x(0), y(0) {};
    Coordinate(Integer x, Integer y) : x(x), y(y) {};
    Coordinate(const Coordinate &coor) : x(coor.x), y(coor.y) {};
    Coordinate(Coordinate&& other) noexcept : x(other.x), y(other.y) {}

    // 重载运算符部分
    // 坐标相加
    Coordinate<Integer> operator+(const Coordinate& coor) const {
        return {x + coor.x, y + coor.y};
    }
    // 坐标加等于另一个坐标
    Coordinate<Integer>& operator+=(const Coordinate& coor) {
        x += coor.x, y += coor.y;
        return *this;
    }
    // 坐标相减
    Coordinate<Integer> operator-(const Coordinate& coor) const {
        return {x - coor.x, y - coor.y};
    }
    // 坐标减等于另一个坐标
    Coordinate<Integer>& operator-=(const Coordinate& coor) {
        x -= coor.x, y -= coor.y;
        return *this;
    }
    // 坐标乘一个整数
    Coordinate<Integer> operator*(const Integer scalar) const {
        return {x * scalar, y * scalar};
    }
    // 坐标乘等于整数
    Coordinate<Integer>& operator*=(const Integer& scalar) {
        this->x *= scalar, this->y *= scalar;
        return *this;
    }
    // 坐标除以一个整数
    Coordinate<Integer> operator/(const Integer num) const {
        return {x / num, y / num};
    }
    // 坐标除等于一个整数
    Coordinate<Integer>& operator/=(const Integer num) {
        this->x /= num, this->y /= num;
        return *this;
    }
    // 坐标取余于一个整数
    Coordinate<Integer> operator%(const Integer num) const {
        return {x % num, t % num};
    }
    // 坐标取余等于一个整数
    Coordinate<Integer> operator%=(const Integer num) {
        this->x %= num, this->y %= num;
        return *this;
    }
    // 判断坐标是否相等
    bool operator==(const Coordinate& coor) const {
        return x == coor.x && y == coor.y;
    }
    // 小于运算符(与哈希函数一起,用于兼容STL容器)(字典序大小)
    bool operator<(const Coordinate& coor) const {
        return x == coor.x ? y < coor.y : x < coor.x;
    }
    // 大于运算符(字典序大小)
    bool operator>(const Coordinate& coor) const {
        return x == coor.x ? y > coor.y : x > coor.x;
    }
    // 小于等于运算符
    bool operator<=(const Coordinate& coor) const {
        return x == coor.x ? y <= coor.y : x <= coor.x;
    }
    // 大于等于运算符
    bool operator>=(const Coordinate& coor) const {
        return x == coor.x ? y >= coor.y : x >= coor.x;
    }
    // 静态成员函数部分
    // 两点间的距离
    static double distance(const Coordinate& coor1, const Coordinate& coor2) {
        if constexpr (std::is_same<Integer, long long>::value) {
            return std::sqrtl((coor1.x - coor2.x) * (coor1.x - coor2.x) + (coor1.y - coor2.y) * (coor1.y - coor2.y));
        } else {
            return std::sqrt((coor1.x - coor2.x) * (coor1.x - coor2.x) + (coor1.y - coor2.y) * (coor1.y - coor2.y));
        }
    }
    // 设置边界上界
    static void setBound(const int xAxisUpBound, const int yAxisUpBound) {
        Coordinate::xAxisUpBound = xAxisUpBound;
        Coordinate::yAxisUpBound = yAxisUpBound;
    }
    // 设置边界下界
    static void setBound(const int xAxisLowBound, const int xAxisUpBound, const int yAxisLowBound, const int yAxisUpBound) {
        Coordinate::xAxisLowBound = xAxisLowBound;
        Coordinate::xAxisUpBound = xAxisUpBound;
        Coordinate::yAxisLowBound = yAxisLowBound;
        Coordinate::yAxisUpBound = yAxisUpBound;
    }
    // 曼哈顿距离
    static Integer manhattan(const Coordinate& a, const Coordinate& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
    // 切比雪夫距离
    static Integer chebyshev(const Coordinate& a, const Coordinate& b) {
        return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
    }

    // 部分功能的实现
    void setPos(int x, int y) {
        this->x = x;
        this->y = y;
    }
    // 判断是否越界
    bool notOutEdge() const noexcept {
        return x >= xAxisLowBound && x <= xAxisUpBound && y >= yAxisLowBound && y <= yAxisUpBound;
    }
    // 获取相邻坐标并过滤越界
    std::vector<Coordinate> neighbors(bool allowDiagonal = false) const noexcept {
        const auto& dirs = allowDiagonal ? directions8 : directions4;
        std::vector<Coordinate<Integer>> ret;
        ret.reserve(allowDiagonal ? 8 : 4);
        for (auto &it : dirs) {
            Coordinate temp = *this + it;
            if (temp.notOutEdge())
                ret.push_back(temp);
        }
        return ret;
    }
    // 重载输出用于调试
    friend std::ostream& operator<<(std::ostream &outStream, const Coordinate& coor) {
        return outStream << '(' << coor.x << ',' << coor.y << ')';
    }
    // 哈希函数支持
    struct Hash
    {
        size_t operator()(const Coordinate& coor) const {
            size_t hash1 = std::hash<Integer>()(coor.x);
            size_t hash2 = std::hash<Integer>()(coor.y);
            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };
    // x1 <= x <= x2 | y1 <= y <= y2
    bool inRectangle(int x1, int y1, int x2, int y2) const {
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);
        return x >= x1 && x <= x2 && y >= y1 && y <= y2;
    }
    // coor1.x <= x <= coor2.y | coor1.y <= y <= coor2.y
    bool inRectangle(Coordinate coor1, Coordinate coor2) const {
        return inRectangle(coor1.x, coor1.y, coor2.x, coor2.y);
    }
};
template <std::integral Integer>
Integer Coordinate<Integer>::xAxisLowBound = 0;

template <std::integral Integer>
Integer Coordinate<Integer>::xAxisUpBound = INT_MAX;

template <std::integral Integer>
Integer Coordinate<Integer>::yAxisLowBound = 0;

template <std::integral Integer>
Integer Coordinate<Integer>::yAxisUpBound = INT_MAX;