#pragma once
#include <functional>
#include <map>
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
		bool Unsubscribe(uint64_t id)
		{
			auto it = _functions.find(id);
			if (it != _functions.end())
			{
				_functions.erase(it);
				return true;
			}

			return false;
		}

	public:
		class UnsubscribeToken
		{
		private:
			uint64_t _id = 0;
			Delegate<ReturnType, Args...> *_delegate;
			friend class Delegate<ReturnType, Args...>;

			UnsubscribeToken(Delegate<ReturnType, Args...> *delegate, uint64_t id)
			{
				_delegate = delegate;
				_id = id;
			}

		public:
			bool Unsubscribe()
			{
				bool result = _delegate->Unsubscribe(_id);
				return result;
			}
		};

		/// @brief 订阅
		/// @param func
		/// @return
		UnsubscribeToken Subscribe(std::function<ReturnType(Args...)> func)
		{
			uint64_t id = _next_id++;
			UnsubscribeToken token{this, id};
			_functions[id] = func;
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
