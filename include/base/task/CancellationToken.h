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
		 * @brief 注册一个委托，当令牌取消时会被调用。
		 *
		 * @note 可以多次调用注册多个委托。
		 *
		 * @param func
		 * @return uint64_t 返回一个 id，用来标识此次注册的委托。取消时可以用此 id 取消。
		 */
		uint64_t Register(std::function<void(void)> func);

		/**
		 * @brief 注销通过 Register 方法注册的委托。
		 *
		 * @param id 委托的 id
		 */
		void Unregister(uint64_t id);
	};
} // namespace base
