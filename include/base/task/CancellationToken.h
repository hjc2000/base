#pragma once
#include "base/define.h"
#include "base/IIdToken.h"
#include "base/string/define.h"
#include "Mutex.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>

namespace base
{
	class CancellationTokenSource;
	class CancellationToken;

	///
	/// @brief 取消令牌
	///
	///
	class CancellationToken final
	{
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

		friend class CancellationTokenSource;

	private:
		CancellationToken() = default;
		DELETE_COPY_AND_MOVE(CancellationToken)

		base::task::Mutex _lock{};
		std::atomic_bool _is_cancellation_request = false;
		std::map<uint64_t, std::function<void(void)>> _delegates;

		inline static uint64_t _id = 0;
		static std::shared_ptr<CancellationToken> _none_cancellation_token;

		void Cancel()
		{
			// 只有取消过一次，即调用本函数一次后，_is_cancellation_request
			// 才会为 true.
			//
			// _is_cancellation_request 为 true 表示已经取消过一次了，
			// 这时候就不要重复取消了。
			if (_is_cancellation_request)
			{
				// 先检查一次，有机会不竞争锁直接能够返回
				return;
			}

			base::task::MutexGuard g{_lock};

			if (_is_cancellation_request)
			{
				// 竞争锁后再次确认
				return;
			}

			_is_cancellation_request = true;

			// 执行列表中的每一个委托
			for (auto const &pair : _delegates)
			{
				pair.second();
			}
		}

	public:
		///
		/// @brief 获取一个不被取消令牌源管理的取消令牌。此令牌永远无法被取消。
		///
		/// @return
		///
		static std::shared_ptr<CancellationToken> const &None()
		{
			return _none_cancellation_token;
		}

		///
		/// @brief 是否需要取消。
		///
		/// @return 为 true 表示已经请求取消了，为 false 表示没有请求取消。
		///
		bool IsCancellationRequested() const
		{
			return _is_cancellation_request;
		}

		///
		/// @brief 如果任务被取消了就抛出异常。
		///
		/// @note 使用本方法可以从深层嵌套中退出，快速结束当前任务。
		///
		void ThrowIfCancellationIsRequested() const
		{
			if (IsCancellationRequested())
			{
				throw std::runtime_error{CODE_POS_STR + "任务取消。"};
			}
		}

		///
		/// @brief 注册一个委托，当令牌取消时会被调用。
		///
		/// @note 可以多次调用注册多个委托。
		///
		/// @param func
		///
		/// @return 用来取消注册委托的 token.
		///
		std::shared_ptr<base::IIdToken> Register(std::function<void(void)> const &func)
		{
			if (this == None().get())
			{
				throw std::runtime_error{"不要对 None 调用 Register 方法"};
			}

			base::task::MutexGuard g{_lock};
			uint64_t current_id = _id++;
			_delegates[current_id] = func;
			return std::shared_ptr<IdToken>{new IdToken{this, current_id}};
		}

		///
		/// @brief 注销通过 Register 方法注册的委托。
		///
		/// @param token 传入由 Register 方法返回的 token.
		///
		void Unregister(std::shared_ptr<base::IIdToken> const &token)
		{
			if (this == None().get())
			{
				return;
			}

			if (token == nullptr)
			{
				throw std::invalid_argument{CODE_POS_STR + "禁止传入空指针。"};
			}

			if (token->Provider() != this)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入了错误的 IIdToken，它不是本对象发放的。"};
			}

			base::task::MutexGuard g{_lock};
			_delegates.erase(token->ID());
		}
	};

} // namespace base
