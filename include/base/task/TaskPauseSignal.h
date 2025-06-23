#pragma once
#include "base/define.h"
#include "base/IDisposable.h"
#include "base/task/TaskCompletionSignal.h"
#include <atomic>

namespace base
{
	///
	/// @brief 任务暂停信号。
	///
	///
	class TaskPauseSignal :
		public base::IDisposable
	{
	private:
		DELETE_COPY_AND_MOVE(TaskPauseSignal)

		std::atomic_bool _should_pause = false;
		std::atomic_bool _disposed = false;

		///
		/// @brief 用来阻塞后台线程的信号。
		///
		///
		base::task::TaskCompletionSignal _block_thread_signal{true};

		///
		/// @brief 发出暂停请求后重置此信号，然后等待。后台线程收到请求后会设置结果。
		///
		///
		base::task::TaskCompletionSignal _response_signal{true};

	public:
		///
		/// @brief 析构时会自动调用 Dispose.
		///
		///
		~TaskPauseSignal();

		///
		/// @brief 释放。让无论是暂停请求还是后台线程都不再被阻塞。
		///
		///
		virtual void Dispose() override;

		///
		/// @brief 请求暂停。
		///
		/// @note 前台线程如果需要暂停后台线程，就调用本方法，等待后台线程调用 Response 方法。
		/// 在这之前，本方法将会阻塞。
		///
		/// @param pause 传入 true 暂停，传入 false 取消暂停。
		///
		void Request(bool pause);

		///
		/// @brief 后台线程始终调用本方法，如果有暂停请求，本方法会回应请求然后陷入阻塞，
		/// 直到取消暂停。
		///
		void Response();
	};

	///
	/// @brief 用来响应 TaskPauseSignal 的守卫。
	///
	/// @note 后台线程函数中需要使用本守卫，防止 UI 线程中发出暂停请求后，后台线程还没响应暂停
	/// 请求，就遇到异常，直接退出了。这就会导致 UI 线程永久卡死。
	///
	class TaskPauseSignalGuard
	{
	private:
		base::TaskPauseSignal &_signal;

	public:
		TaskPauseSignalGuard(base::TaskPauseSignal &signal);

		///
		/// @brief 析构。会 Dispose base::TaskPauseSignal, 使其不再能够使用。
		///
		///
		~TaskPauseSignalGuard();
	};

} // namespace base
