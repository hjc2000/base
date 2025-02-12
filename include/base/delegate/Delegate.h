#pragma once
#include <base/delegate/IEvent.h>
#include <base/task/IMutex.h>
#include <map>
#include <stdint.h>

namespace base
{
	/// @brief 委托类
	/// @note 本类继承了 IEvent 接口。一个类如果只想让外部订阅和取消订阅，不想让外部能够触发事件，
	/// 则可以将 Delegate 对象作为私有字段，然后提供一个函数，返回 IEvent 的引用，这样外部就只能订阅和
	/// 取消订阅，无法触发事件了。
	/// @tparam ...Args
	template <typename... Args>
	class Delegate final :
		public base ::IEvent<Args...>
	{
	private:
		std::map<uint64_t, std::function<void(Args...)>> _functions;
		uint64_t _next_id = 0;
		mutable std::shared_ptr<base::IMutex> _lock = base::di::CreateMutex();

		/// @brief 取消订阅方法
		/// @param id
		/// @return
		void Unsubscribe(uint64_t id)
		{
			base::LockGuard g{*_lock};
			auto it = _functions.find(id);
			if (it != _functions.end())
			{
				_functions.erase(it);
			}
		}

	public:
		/// @brief 订阅
		/// @param func 要订阅的回调
		/// @return 返回用来取消订阅的令牌。
		/// @warning 禁止在 Delegate 对象析构后使用取消令牌。
		std::shared_ptr<base::IUnsubscribeToken> Subscribe(std::function<void(Args...)> func) override
		{
			class UnsubscribeToken final :
				public base::IUnsubscribeToken
			{
			public:
				uint64_t _id = 0;
				Delegate<Args...> *_delegate;

				virtual void Unsubscribe() override
				{
					_delegate->Unsubscribe(_id);
				}
			};

			base::LockGuard g{*_lock};
			std::shared_ptr<UnsubscribeToken> token{new UnsubscribeToken{}};
			token->_id = _next_id++;
			token->_delegate = this;
			_functions[token->_id] = func;
			return token;
		}

		/// @brief 调用所有订阅的函数
		/// @param ...args
		void Invoke(Args... args) const
		{
			base::LockGuard g{*_lock};
			for (auto &func : _functions)
			{
				func.second(args...);
			}
		}

		/// @brief 伪函数
		/// @param ...args
		void operator()(Args... args) const
		{
			Invoke(args...);
		}
	};
} // namespace base
