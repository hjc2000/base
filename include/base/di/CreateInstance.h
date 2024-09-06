#pragma once
#include <stdexcept>

namespace base
{
    /// @brief 创建一个实例。用来实现依赖注入。
    /// @tparam SingletonType
    /// @return
    template <typename SingletonType>
    SingletonType &CreateInstance()
    {
        throw std::runtime_error{"未实现的特化版本"};
    }
} // namespace base