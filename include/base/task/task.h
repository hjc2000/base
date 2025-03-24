#pragma once
#include <cstdint>
#include <functional>

namespace base
{
	namespace task
	{
		///
		/// @brief 默认的任务栈大小。
		///
		/// @return int64_t
		///
		int64_t DefaultTaskStackSize();

		///
		/// @brief 设置默认的任务栈大小。
		///
		/// @param value
		///
		void SetDefaultTaskStackSize(int64_t value);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func
		///
		void Run(std::function<void()> func);

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func
		/// @param stack_size 任务栈大小。单位：字节。有些平台例如 freertos 需要这个参数。
		///
		void Run(std::function<void()> func, int64_t stack_size);

	} // namespace task
} // namespace base
