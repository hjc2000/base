#pragma once
#include "base/task/TaskCompletionSignal.h"
#include <cstdint>
#include <functional>
#include <memory>

namespace base
{
	namespace task
	{
		///
		/// @brief 默认的任务栈大小。
		///
		/// @return int64_t
		///
		int64_t default_task_stack_size();

		///
		/// @brief 设置默认的任务栈大小。
		///
		/// @param value
		///
		void set_default_task_stack_size(int64_t value);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func
		///
		/// @return std::shared_ptr<base::TaskCompletionSignal>
		///
		std::shared_ptr<base::TaskCompletionSignal> run(std::function<void()> const &func);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func
		/// @param stack_size 任务栈大小。单位：字节。有些平台例如 freertos 需要这个参数。
		///
		/// @return std::shared_ptr<base::TaskCompletionSignal>
		///
		std::shared_ptr<base::TaskCompletionSignal> run(std::function<void()> const &func, int64_t stack_size);

	} // namespace task
} // namespace base
