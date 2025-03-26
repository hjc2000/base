#pragma once
#include "base/IIdToken.h"
#include <functional>
#include <memory>

namespace base
{
	template <typename... Args>
	class IEvent
	{
	public:
		///
		/// @brief 订阅事件。
		///
		/// @param func
		/// @return std::shared_ptr<typename base::IIdToken> 用来取消订阅的 token.
		///
		virtual std::shared_ptr<base::IIdToken> Subscribe(std::function<void(Args...)> func) = 0;

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		virtual void Unsubscribe(std::shared_ptr<base::IIdToken> const &token) = 0;
	};
} // namespace base
