#pragma once
#if HAS_THREAD

#include <atomic>
#include <base/task/IDisposableSemaphore.h>
#include <semaphore>

namespace base
{
	class DisposableSemaphore_InitialCount
	{
	private:
		int32_t _value = 0;

	public:
		explicit DisposableSemaphore_InitialCount(int32_t value)
			: _value(value)
		{
		}

		int32_t Value() const
		{
			return _value;
		}
	};

	class DisposableSemaphore :
		public base::IDisposableSemaphore
	{
	private:
		std::counting_semaphore<INT32_MAX> _semaphore{0};
		std::atomic_bool _disposed = false;

	public:
		DisposableSemaphore(base::DisposableSemaphore_InitialCount const &initial_count);

		virtual void Dispose() override;

		/// @brief 释放信号量。
		/// @param count 要释放的数量。
		virtual void Release(int32_t count) override;

		/// @brief 获取信号量。无限等待，永不超时。
		virtual void Acquire() override;

		/// @brief 尝试获取信号量。超时后会失败，并返回 false，成功获取信号量后将
		/// 返回 true.
		/// @param timeout 超时时间。
		/// @return
		virtual bool TryAcquire(base::Seconds const &timeout) override;
	};
} // namespace base

#endif // HAS_THREAD
