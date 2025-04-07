#include <vector>
#include <string>

// 生成next数组（前缀表）
std::vector<int> getNext(const std::string& pattern) {
    int n = pattern.size();
    std::vector<int> next(n, 0);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

// KMP主算法
std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    if (pattern.empty()) return matches;
    
    std::vector<int> next = getNext(pattern);
    int m = text.size(), n = pattern.size();
    
    for (int i = 0, j = 0; i < m; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == n) {
            matches.push_back(i - n + 1);
            j = next[j - 1];
        }
    }
    return matches;
}