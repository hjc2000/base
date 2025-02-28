#pragma once
#include "base/string/define.h"
#include <base/delegate/IEvent.h>
#include <base/task/IMutex.h>
#include <cstdint>
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
		public base::IEvent<Args...>
	{
	private:
		mutable std::shared_ptr<base::IMutex> _lock = base::di::CreateIMutex();
		std::map<uint64_t, std::function<void(Args...)>> _functions;
		uint64_t _next_id = 0;

	private:
		class IdToken :
			public base::IIdToken
		{
		private:
			void *_id_provider = nullptr;
			uint64_t _id = 0;

		public:
			IdToken(void *id_provider, uint64_t id)
				: _id_provider(id_provider),
				  _id(id)
			{
			}

		public:
			virtual void *Provider() const override
			{
				return _id_provider;
			}

			virtual uint64_t ID() const override
			{
				return _id;
			}
		};

	public:
		/**
		 * @brief 订阅事件。
		 *
		 * @param func
		 * @return std::shared_ptr<base::IIdToken> 用来取消订阅的 token.
		 */
		virtual std::shared_ptr<base::IIdToken> Subscribe(std::function<void(Args...)> const &func) override
		{
			base::LockGuard g{*_lock};
			uint64_t id = _next_id++;
			_functions[id] = func;
			return std::shared_ptr<IdToken>{new IdToken{this, id}};
		}

		/**
		 * @brief 取消订阅事件。
		 *
		 * @param token 传入由 Subscribe 方法返回的 token.
		 */
		virtual void Unsubscribe(std::shared_ptr<typename base::IIdToken> const &token) override
		{
			if (token == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			if (token->Provider() != this)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入了错误的 IIdToken，它不是本对象发放的。"};
			}

			base::LockGuard g{*_lock};
			auto it = _functions.find(token->ID());
			if (it != _functions.end())
			{
				_functions.erase(it);
			}
		}

	public:
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
