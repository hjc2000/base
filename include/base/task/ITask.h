#pragma once

namespace base
{
	namespace task
	{
		class ITask
		{
		public:
			virtual ~ITask() = default;

			///
			/// @brief 任务已经完成。
			///
			/// @return 已完成会返回 true，否则返回 false.
			///
			virtual bool IsCompleted() const = 0;

			///
			/// @brief 等待任务完成。会阻塞当前线程。
			///
			///
			virtual void Wait() = 0;
		};

	} // namespace task
} // namespace base
