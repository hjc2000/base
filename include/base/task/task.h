#pragma once
#include "base/task/ITask.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

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

		/* #region run */

		///
		/// @brief 运行一个任务。
		///
		/// @note 实现者需要将后台线程实现为捕获所有异常，输出错误消息。
		///
		/// @param func 任务函数。
		///
		/// @return
		///
		std::shared_ptr<base::task::ITask> run(std::function<void()> const &func);

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
		std::shared_ptr<base::task::ITask> run(size_t stack_size,
											   std::function<void()> const &func);

		///
		/// @brief 运行一个任务。
		///
		/// @param priority 任务优先级。
		/// @param stack_size 任务栈大小。单位：字节。
		/// @param func 任务函数。
		///
		/// @return
		///
		std::shared_ptr<base::task::ITask> run(uint32_t priority,
											   size_t stack_size,
											   std::function<void()> const &func);

		///
		/// @brief 运行一个任务。
		///
		/// @param task_name 任务名。
		/// @param priority 任务优先级。
		/// @param stack_size 任务栈大小。单位：字节。
		/// @param func 任务函数。
		///
		/// @return
		///
		std::shared_ptr<base::task::ITask> run(std::string const &task_name,
											   uint32_t priority,
											   size_t stack_size,
											   std::function<void()> const &func);

		/* #endregion */

		/* #region 调度管理 */

		///
		/// @brief 启动调度。
		///
		/// @note 有的平台需要手动启动调度。例如 freertos. 如果平台不需要手动启动调度，
		/// 则不实现此函数。
		///
		void start_scheduler();

		///
		/// @brief 任务调度已经开始了。
		///
		/// @return
		///
		bool scheduler_has_started();

		///
		/// @brief 暂停所有任务的调度。
		///
		///
		void suspend_all_task_scheduler();

		///
		/// @brief 恢复所有任务的调度。
		///
		///
		void resume_all_task_scheduler();

		///
		/// @brief 任务调度暂停守卫。
		///
		/// @note 构造时暂停所有任务的调度，析构时恢复所有任务的调度。
		///
		///
		class TaskSchedulerSuspendGuard
		{
		public:
			TaskSchedulerSuspendGuard()
			{
				suspend_all_task_scheduler();
			}

			~TaskSchedulerSuspendGuard()
			{
				resume_all_task_scheduler();
			}
		};

		/* #endregion */

	} // namespace task
} // namespace base
