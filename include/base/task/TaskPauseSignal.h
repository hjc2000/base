#pragma once
#include "base/task/TaskCompletionSignal.h"
#include <atomic>

namespace base
{
	///
	/// @brief 任务暂停信号。
	///
	///
	class TaskPauseSignal
	{
	private:
		std::atomic_bool _should_pause = false;

		///
		/// @brief 用来阻塞后台线程的信号。
		///
		///
		base::TaskCompletionSignal _block_thread_signal{true};

		///
		/// @brief 发出暂停请求后重置此信号，然后等待。后台线程收到请求后会设置结果。
		///
		///
		base::TaskCompletionSignal _response_signal{true};

	public:
		///
		/// @brief 请求暂停。
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
} // namespace base
