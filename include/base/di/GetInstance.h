#pragma once
#include <memory>
#include <stdexcept>

namespace base
{
    /// @brief 获取实例。
    /// @note 不要求是单例还是多例。依赖提供者自由决定。
    /// @tparam T
    /// @return
    template <typename T>
    std::shared_ptr<T> GetInstance()
    {
        static_assert(false, "未实现的特化版本");
        throw std::runtime_error{"未实现的特化版本"};
    }

} // namespace base
