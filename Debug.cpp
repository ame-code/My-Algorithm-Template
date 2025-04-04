#include<bits/stdc++.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
    for(int i = (os << '[', 0); i < vec.size(); i++, os << (",]"[i == vec.size()])) {
        os << vec[i];
    }
    return os;
}

int main() {
    std::vector<std::vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
    std::cout << a;
    system("pause");
    return 0;
}