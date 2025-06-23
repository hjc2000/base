#pragma once
#include "base/IIdToken.h"
#include <functional>

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
		///
		/// @return 用来取消订阅的 token.
		///
		virtual base::SpIIdToken Subscribe(std::function<void(Args...)> const &func) = 0;

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		virtual void Unsubscribe(base::SpIIdToken const &token) = 0;

		///
		/// @brief 订阅事件。
		///
		/// @param func
		///
		/// @return 用来取消订阅的 token.
		///
		base::SpIIdToken operator+=(std::function<void(Args...)> const &func)
		{
			return Subscribe(func);
		}

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		void operator-=(base::SpIIdToken const &token)
		{
			Unsubscribe(token);
		}
	};

} // namespace base
