#pragma once

namespace base
{
	/// @brief 取消订阅令牌
	/// @warning 禁止在发放令牌的对象析构后使用令牌
	class IUnsubscribeToken
	{
	public:
		/// @brief 取消订阅委托。
		virtual void Unsubscribe() = 0;
	};
} // namespace base
