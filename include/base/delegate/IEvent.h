#pragma once
#include <functional>
#include <memory>

namespace base
{
	template <typename... Args>
	class IEvent
	{
	public:
		class IIdToken
		{
		public:
			virtual uint64_t ID() const = 0;
		};

	public:
		/**
		 * @brief 订阅事件。
		 *
		 * @param func
		 * @return std::shared_ptr<base::IIdToken> 用来取消订阅的 token.
		 */
		virtual std::shared_ptr<typename base::IEvent<Args...>::IIdToken> Subscribe(std::function<void(Args...)> const &func) = 0;

		/**
		 * @brief 取消订阅事件。
		 *
		 * @param token 传入由 Subscribe 方法返回的 token.
		 */
		virtual void Unsubscribe(typename std::shared_ptr<base::IEvent<Args...>::IIdToken> const &token) = 0;
	};
} // namespace base
