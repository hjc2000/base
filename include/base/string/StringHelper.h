#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace base
{
    /// @brief 以某个字符为分隔符分割字符串。
    /// @param str 要被分割地字符串。
    /// @param delimiter 分隔符。
    /// @return 字符串被分割后会将每一个字符串放到向量中。
    std::vector<std::string> Split(std::string const &str, char delimiter);
} // namespace base
