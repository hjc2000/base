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

	/// @brief 取消令牌
	/// @warning 没有将宏变量 HAS_THREAD 定义为真的话，本类的所有操作都没有互斥锁保护，
	/// 此时只有 IsCancellationRequested 方法是线程安全的，因为它只读。
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
		/**
		 * @brief 取消注册令牌。用于取消注册通过 CancellationToken::Register 方法注册的委托。
		 *
		 */
		class UnregisterToken
		{
		private:
			friend class CancellationToken;
			uint64_t const _id{};

		private:
			UnregisterToken(uint64_t id)
				: _id(id)
			{
			}
		};

		/**
		 * @brief 注册一个委托，当令牌取消时会被调用。
		 *
		 * @note 可以多次调用注册多个委托。
		 *
		 * @param func
		 * @return uint64_t 返回一个 id，用来标识此次注册的委托。取消时可以用此 id 取消。
		 */
		UnregisterToken Register(std::function<void(void)> const &func);

		/**
		 * @brief 注销通过 Register 方法注册的委托。
		 *
		 * @param token 委托的 id
		 */
		void Unregister(UnregisterToken const &token);
	};
} // namespace base
