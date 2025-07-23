#pragma once
#include "base/delegate/IEvent.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/Mutex.h"
#include <atomic>
#include <cstdint>
#include <map>

namespace base
{
	///
	/// @brief 委托类。
	///
	/// @note 本类继承了 IEvent 接口。一个类如果只想让外部订阅和取消订阅，不想让外部能够触发事件，
	/// 则可以将 Delegate 对象作为私有字段，然后提供一个函数，返回 IEvent 的引用，
	/// 这样外部就只能订阅和取消订阅，无法触发事件了。
	///
	template <typename... Args>
	class Delegate final :
		public base::IEvent<Args...>,
		public base::IDisposable
	{
	private:
		base::task::Mutex _lock{};
		std::map<uint64_t, std::function<void(Args...)>> _functions;
		uint64_t _next_id = 0;
		std::atomic_bool _disposed = false;

	private:
		/* #region IdToken */

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

			virtual void *Provider() const override
			{
				return _id_provider;
			}

			virtual uint64_t ID() const override
			{
				return _id;
			}
		};

		/* #endregion */

	public:
		~Delegate()
		{
			Dispose();
		}

		///
		/// @brief 释放后会清空委托 map, 并且无法再订阅或调用委托。
		///
		/// @note 因为委托 map 被清空了，所以也不需要取消订阅了，取消订阅操作也会引发异常。
		///
		/// @note 与 Invoke 以及其他方法互斥。也就是说如果 Invoke 正在执行，本方法会等待
		/// 互斥锁的释放，然后才清空委托 map.
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				return;
			}

			_disposed = true;
			_functions.clear();
		}

		///
		/// @brief 订阅事件。
		///
		/// @param func
		///
		/// @return 用来取消订阅的 token.
		///
		virtual base::SpIIdToken Subscribe(std::function<void(Args...)> const &func) override
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后无法订阅。"};
			}

			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后无法订阅。"};
			}

			uint64_t id = _next_id++;
			_functions[id] = func;
			return base::SpIIdToken{new IdToken{this, id}};
		}

		///
		/// @brief 取消订阅事件。
		///
		/// @param token 传入由 Subscribe 方法返回的 token.
		///
		virtual void Unsubscribe(base::SpIIdToken const &token) override
		{
			if (token == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			if (token->Provider() != this)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入了错误的 IIdToken，它不是本对象发放的。"};
			}

			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后不需要取消订阅，因为委托 map 清空了。"};
			}

			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后不需要取消订阅，因为委托 map 清空了。"};
			}

			auto it = _functions.find(token->ID());
			if (it != _functions.end())
			{
				_functions.erase(it);
			}
		}

		///
		/// @brief 调用所有订阅的函数
		///
		/// @param ...args
		///
		void Invoke(Args... args)
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后无法调用。"};
			}

			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				throw base::ObjectDisposedException{CODE_POS_STR + "释放后无法调用。"};
			}

			for (auto &func : _functions)
			{
				func.second(args...);
			}
		}

		///
		/// @brief 伪函数
		///
		/// @param ...args
		///
		void operator()(Args... args)
		{
			Invoke(args...);
		}
	};

} // namespace base
