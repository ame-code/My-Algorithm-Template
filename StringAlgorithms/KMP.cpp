#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 获取模式串的next数组（下标从0开始）
vector<int> computeNext(const string &pattern) {
    int m = pattern.size();
    vector<int> next(m, 0);    // next数组初始化
    next[0] = -1;              // 初始值为-1（无匹配前缀）
    int j = 0, k = -1;

    while (j < m - 1) {
        // 当字符匹配或k回溯到起点时更新next数组
        if (k == -1 || pattern[j] == pattern[k]) {
            j++;
            k++;
            next[j] = k;       // 当前位置的最长前缀后缀长度
        } else {
            k = next[k];       // 不匹配时回溯到前一个最长前缀位置[7,8](@ref)
        }
    }
    return next;
}

// KMP主算法（返回所有匹配的起始位置）
vector<int> kmpSearch(const string &text, const string &pattern) {
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    if (m == 0 || n < m) return matches;

    vector<int> next = computeNext(pattern); // 预计算next数组[1,10](@ref)
    int i = 0, j = 0;

    while (i < n) {
        // 当字符匹配或j回溯到起点时移动指针
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];       // 根据next数组跳过无效匹配[3,5](@ref)
        }

        // 找到完全匹配的子串
        if (j == m) {
            matches.push_back(i - m);
            j = next[j - 1];   // 继续寻找下一个可能的匹配[11](@ref)
        }
    }
    return matches;
}

// 测试示例
int main() {
    system("chcp 65001 > nul");

    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    vector<int> result = kmpSearch(text, pattern);
    if (!result.empty()) {
        cout << "匹配起始位置：";
        for (int pos : result) cout << pos << " ";
    } else {
        cout << "未找到匹配项";
    }
    system("pause");
    return 0;
}