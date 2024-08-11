#pragma once
#include <base/task/CancellationToken.h>

namespace base
{
    /// @brief 取消令牌源
    class CancellationTokenSource final
    {
    private:
        std::shared_ptr<CancellationToken> _token{new CancellationToken{}};

    public:
        bool IsCancellationRequested() const;
        std::shared_ptr<CancellationToken> Token() const;

        /// @brief 取消
        /// @warning 没有将宏变量 HAS_THREAD 定义为真的话，本方法禁止在多个线程中调用，
        /// 因为此时缺少互斥锁保护。
        void Cancel();
    };
} // namespace base
