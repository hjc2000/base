#pragma once
#include <functional>

namespace base
{
	namespace task
	{
		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func
		///
		void Run(std::function<void()> func);

	} // namespace task
} // namespace base
