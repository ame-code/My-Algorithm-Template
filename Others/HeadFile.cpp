#include<bits/stdc++.h>

namespace ranges = std::ranges;
namespace views = std::views;

/*
    - **`-g`**  
    生成调试信息（符号表、行号等），允许使用 GDB 等工具调试程序。即使与 `-O2` 优化同时使用，仍会保留调试信息（但可能限制部分优化效果）。
    ---
    ### **3. 诊断与警告控制**
    - **`-fdiagnostics-color=always`**  
    强制编译器输出带颜色的错误/警告信息，提高可读性。
    - **`-Wall`**  
    启用所有常规警告（如未使用变量、类型转换问题等）。
    - **`-Wextra`**  
    启用额外警告（如空循环、逻辑表达式冗余等），补充 `-Wall` 未覆盖的检查项。
    - **`-Werror`**  
    将所有警告视为错误，强制开发者解决所有警告问题，避免潜在缺陷。
    - **`-Wshadow`**  
    检测变量遮蔽（如局部变量与全局变量同名）。
    - **`-Wconversion`** 与 **`-Wsign-conversion`**  
    检查隐式类型转换和符号转换（如 `int` 转 `unsigned` 可能导致的数值错误）。
    ---
    - **`-fsanitize=address,undefined,leak`**  
    启用三大检测工具：  
    - **AddressSanitizer (ASan)**：检测内存越界、释放后使用等问题。  
    - **UndefinedBehaviorSanitizer (UBSan)**：检测未定义行为（如整数溢出、空指针解引用）。  
    - **LeakSanitizer (LSan)**：检测内存泄漏。  
    这些工具在运行时生效，显著增加程序开销，但能捕捉隐蔽错误。

    - **`-ftrapv`**  
    在检测到有符号整数溢出时触发陷阱（程序终止），增强对未定义行为的防御。

    ---

    ### **5. 标准库调试支持**
    - **`-D_GLIBCXX_DEBUG`**  
    启用 GNU 标准库的调试模式，添加容器边界检查、迭代器有效性验证等功能，防止如 `std::vector` 越界访问等问题。

    ---

    ### **6. 输出与目标文件**
    - **`-o test`**  
    指定输出文件名为 `test`，代替默认的 `a.out`。

    ---

    ### **总结**
    这些参数组合旨在：  
    1. 确保代码符合现代 C++ 标准（C++20）。  
    2. 平衡性能优化与调试信息保留。  
    3. 通过严格的警告和错误检查提升代码质量。  
    4. 启用运行时检测工具捕捉内存问题与未定义行为。  
    5. 增强标准库的安全性（如容器边界检查）。  

    适合需要高可靠性的开发环境（如测试、调试阶段），但可能因检测工具和调试模式增加运行时开销，生产环境需酌情调整。
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