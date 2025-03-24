#pragma once

#include <functional>

namespace base
{
	namespace task
	{
		///
		/// @brief 运行一个任务。
		///
		/// @param func
		///
		void Run(std::function<void()> func);

	} // namespace task
} // namespace base
