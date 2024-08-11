#pragma once
#include <base/delegate/IUnsubscribeToken.h>
#include <functional>
#include <memory>

namespace base
{
    template <typename... Args>
    class IEvent
    {
    public:
        virtual ~IEvent() = default;

        /// @brief 订阅
        /// @param func 要订阅的回调
        /// @return 返回用来取消订阅的令牌。
        /// @warning 禁止在 Delegate 对象析构后使用取消令牌。
        virtual std::shared_ptr<base::IUnsubscribeToken> Subscribe(std::function<void(Args...)> func) = 0;
    };
} // namespace base
