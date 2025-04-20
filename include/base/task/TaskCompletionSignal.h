#pragma once
#include "base/define.h"
#include "base/task/IMutex.h"
#include "Semaphore.h"
#include <atomic>
#include <memory>

namespace base
{
	///
	/// @brief 任务完成信号。
	///
	///
	class TaskCompletionSignal final
	{
	private:
		DELETE_COPY_AND_MOVE(TaskCompletionSignal)

		///
		/// @brief 共享指针本身不是线程安全的，多线程同时读写需要加锁。
		///
		///
		mutable std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();

		///
		/// @brief 共享指针本身不是线程安全的，多线程同时读写需要加锁。
		///
		///
		std::shared_ptr<base::Semaphore> _semaphore = nullptr;

		std::atomic_bool _disposed = false;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param completed 任务初始时是否处于已完成状态。
		///
		TaskCompletionSignal(bool completed);

		///
		/// @brief 析构函数。析构时会调用 Dispose 方法。
		///
		///
		~TaskCompletionSignal();

		///
		/// @brief 释放后，本对象将不再具有阻塞的能力，正在阻塞的 Wait 会立刻停止阻塞。
		///
		void Dispose();

		///
		/// @brief 如果 Dispose 被调用，本方法将永远返回 true，此时任务被锁定在完成状态，Reset
		/// 方法不再具有效果。这种情况下，本对象的 Wait 将不再具有阻塞的能力。
		///
		/// @return
		///
		bool IsCompleted() const;

		///
		/// @brief 等待，直到完成信号被触发。
		///
		void Wait();

		///
		/// @brief 触发完成信号。
		///
		void SetResult();

		///
		/// @brief 重置完成状态。重置完了之后下一次 Wait 将会被阻塞。
		///
		void Reset();
	};
} // namespace base
