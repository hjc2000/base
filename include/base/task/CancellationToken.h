#pragma once
#include "base/define.h"
#include "base/IIdToken.h"
#include "base/task/IMutex.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>

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

		CancellationToken() = default;
		CancellationToken(CancellationToken const &o) = delete;
		CancellationToken &operator=(CancellationToken const &o) = delete;
		CancellationToken(CancellationToken const &&o) = delete;
		CancellationToken &operator=(CancellationToken const &&o) = delete;

		friend class CancellationTokenSource;
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
		std::atomic_bool _is_cancellation_request = false;
		std::map<uint64_t, std::function<void(void)>> _delegates;

		inline static_field uint64_t _id = 0;
		static_field std::shared_ptr<CancellationToken> _none_cancellation_token;

		void Cancel();

	public:
		///
		/// @brief 获取一个不被取消令牌源管理的取消令牌。此令牌永远无法被取消。
		///
		/// @return static_function
		///
		static_function std::shared_ptr<CancellationToken> None();

		///
		/// @brief 是否需要取消。
		///
		/// @return true
		/// @return false
		///
		bool IsCancellationRequested() const;

		///
		/// @brief 如果任务被取消了就抛出异常。
		///
		/// @note 使用本方法可以从深层嵌套中退出，快速结束当前任务。
		///
		void ThrowIfCancellationIsRequested() const;

		///
		/// @brief 注册一个委托，当令牌取消时会被调用。
		///
		/// @param func @note 可以多次调用注册多个委托。
		///
		/// @return std::shared_ptr<base::IIdToken> 用来取消注册委托的 token.
		///
		std::shared_ptr<base::IIdToken> Register(std::function<void(void)> const &func);

		///
		/// @brief 注销通过 Register 方法注册的委托。
		///
		/// @param token 传入由 Register 方法返回的 token.
		///
		void Unregister(std::shared_ptr<base::IIdToken> const &token);
	};
} // namespace base
