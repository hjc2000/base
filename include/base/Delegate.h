#pragma once
#include <base/IUnsubscribeToken.h>
#include <functional>
#include <map>
#include <memory>
#include <stdint.h>

namespace base
{
	template <typename ReturnType, typename... Args>
	class Delegate
	{
	private:
		std::map<uint64_t, std::function<ReturnType(Args...)>> _functions;
		uint64_t _next_id = 0;

		/// @brief 取消订阅方法
		/// @param id
		/// @return
		void Unsubscribe(uint64_t id)
		{
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
		std::shared_ptr<base::IUnsubscribeToken> Subscribe(std::function<ReturnType(Args...)> func)
		{
			class UnsubscribeToken
				: public base::IUnsubscribeToken
			{
			public:
				uint64_t _id = 0;
				Delegate<ReturnType, Args...> *_delegate;

				void Unsubscribe() override
				{
					_delegate->Unsubscribe(_id);
				}
			};

			std::shared_ptr<UnsubscribeToken> token{new UnsubscribeToken{}};
			token->_id = _next_id++;
			token->_delegate = this;
			_functions[token->_id] = func;
			return token;
		}

		/// @brief 调用所有订阅的函数
		/// @param ...args
		void Invoke(Args... args)
		{
			for (auto &func : _functions)
			{
				func.second(args...);
			}
		}

		void operator()(Args... args)
		{
			Invoke(args...);
		}
	};
} // namespace base
