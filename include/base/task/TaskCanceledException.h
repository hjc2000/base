#pragma once
#include <stdexcept>

namespace base
{
    /// @brief 任务取消后抛出此异常。
    /// @note 建议抛出，因为这有助于帮助后台线程停下来。
    class TaskCanceledException final : public std::runtime_error
    {
    public:
        TaskCanceledException()
            : runtime_error(__func__)
        {
        }

        TaskCanceledException(char const *msg)
            : runtime_error(std::string(__func__) + " " + msg)
        {
        }

        TaskCanceledException(std::string msg)
            : runtime_error(std::string(__func__) + " " + msg)
        {
        }
    };
} // namespace base
