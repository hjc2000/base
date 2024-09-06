#pragma once
#include <stdexcept>

namespace base
{
    /// @brief 获取单例。用来实现依赖注入。
    /// @tparam T
    /// @return
    template <typename T>
    T &GetSingletonInstance()
    {
        static_assert(false, "未实现的特化版本");
        throw std::runtime_error{"未实现的特化版本"};
    }
} // namespace base
