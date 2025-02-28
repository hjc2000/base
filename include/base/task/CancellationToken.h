#pragma once
#include <atomic>
#include <base/define.h>
#include <base/task/IMutex.h>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>

namespace base
{
	class CancellationTokenSource;
	class CancellationToken;
	class IdToken;

	/**
	 * @brief 取消令牌
	 *
	 */
	class CancellationToken final
	{
	private:
		CancellationToken() = default;

	private:
		friend class CancellationTokenSource;
		std::shared_ptr<base::IMutex> _lock = base::di::CreateMutex();
		std::atomic_bool _is_cancellation_request = false;
		std::map<uint64_t, std::function<void(void)>> _delegates;

		inline static_field uint64_t _id = 0;
		static_field std::shared_ptr<CancellationToken> _none_cancellation_token;

		void Cancel();

	public:
		/**
		 * @brief 获取一个不被取消令牌源管理的取消令牌。此令牌永远无法被取消。
		 *
		 * @return static_function
		 */
		static_function std::shared_ptr<CancellationToken> None();

		/**
		 * @brief 是否需要取消
		 *
		 * @return true
		 * @return false
		 */
		bool IsCancellationRequested() const;

	public:
		class IIdToken
		{
		public:
			virtual uint64_t ID() const = 0;
		};

	private:
		class IdToken :
			public IIdToken
		{
		private:
			uint64_t const _id{};

		public:
			IdToken(uint64_t id)
				: _id(id)
			{
			}

			IdToken(IdToken const &o) = delete;
			IdToken &operator=(IdToken const &o) = delete;

		public:
			virtual uint64_t ID() const override
			{
				return _id;
			}
		};

	public:
		/**
		 * @brief 注册一个委托，当令牌取消时会被调用。
		 *
		 * @note 可以多次调用注册多个委托。
		 *
		 * @param func
		 * @return std::shared_ptr<base::IdToken> 用来取消注册委托的 token.
		 */
		std::shared_ptr<base::CancellationToken::IIdToken> Register(std::function<void(void)> const &func);

		/**
		 * @brief 注销通过 Register 方法注册的委托。
		 *
		 * @param token 传入由 Register 方法返回的 token.
		 */
		void Unregister(std::shared_ptr<base::CancellationToken::IIdToken> const &token);
	};
} // namespace base
