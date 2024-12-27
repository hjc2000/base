#pragma once
#if HAS_THREAD

#include <atomic>
#include <base/task/IDisposableSemaphore.h>
#include <mutex>
#include <semaphore>

namespace base
{
	class DisposableSemaphore_MaxCount
	{
	private:
		int32_t _value = 0;

	public:
		explicit DisposableSemaphore_MaxCount(int32_t value)
			: _value(value)
		{
		}

		int32_t Value() const
		{
			return _value;
		}
	};

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
		std::mutex _lock;
		std::counting_semaphore<INT32_MAX> _semaphore{0};
		std::atomic_bool _disposed = false;
		int64_t _max_count = 1;

		/// @brief 被释放的信号量的数量。
		/// @note 为正数时表示等会儿如果有这么多个线程获取信号量，可以不被阻塞直接通过。
		/// @note 因为本类获取信号量的方法会在获取前递减本字段，所以本字段如果为负数，就表示
		/// 当前有此负数的相反数这么多个线程正在等待信号量。
		/// @note 为 0 表示没有预先释放，等会儿如果有 1 个线程试图获取信号量，将会被阻塞。
		/// 并且此时也没有线程调用了 Acquire 或 TryAcquire 试图获取信号量。
		int64_t _released_count = 0;

	public:
		DisposableSemaphore(base::DisposableSemaphore_MaxCount const &max_count,
							base::DisposableSemaphore_InitialCount const &initial_count);

		~DisposableSemaphore()
		{
			Dispose();
		}

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
