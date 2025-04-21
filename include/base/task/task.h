#pragma once
#include "base/task/TaskCompletionSignal.h"
#include <cstddef>
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
		size_t default_task_stack_size();

		///
		/// @brief 设置默认的任务栈大小。
		///
		/// @param value
		///
		void set_default_task_stack_size(size_t value);

		///
		/// @brief 任务的默认优先级。
		///
		/// @return
		///
		uint32_t default_priority();

		///
		/// @brief 设置任务的默认优先级。
		///
		/// @param value
		///
		void set_default_priority(uint32_t value);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func 任务函数。
		///
		/// @return
		///
		std::shared_ptr<base::TaskCompletionSignal> run(std::function<void()> const &func);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param stack_size 任务栈大小。单位：字节。有些平台例如 freertos 需要这个参数。
		/// @param func 任务函数。
		///
		/// @return
		///
		std::shared_ptr<base::TaskCompletionSignal> run(size_t stack_size, std::function<void()> const &func);

		///
		/// @brief 运行一个任务。
		///
		/// @param priority 任务优先级。
		/// @param stack_size 任务栈大小。单位：直接。
		/// @param func 任务函数。
		/// @return
		///
		std::shared_ptr<base::TaskCompletionSignal> run(uint32_t priority,
														size_t stack_size,
														std::function<void()> const &func);

	} // namespace task
} // namespace base
