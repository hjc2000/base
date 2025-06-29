#pragma once
#include "base/container/BlockingQueue.h"
#include "base/IDisposable.h"
#include "ITask.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace base
{
	namespace task
	{
		class ThreadPool final :
			base::IDisposable
		{
		private:
			class Task;
			class Worker;

			int32_t _thread_count = 1;
			std::vector<std::shared_ptr<Worker>> _workers;
			base::BlockingQueue<std::shared_ptr<Task>> _task_queue;
			std::atomic_bool _disposed = false;

		public:
			ThreadPool(int32_t thread_count);

			~ThreadPool()
			{
				Dispose();
			}

			///
			/// @brief 主动释放对象，让对象不再能够工作。
			///
			///
			virtual void Dispose() override;

			///
			/// @brief 线程池是否已被释放。
			///
			/// @return
			///
			bool Disposed() const
			{
				return _disposed;
			}

			///
			/// @brief 向线程池中添加任务，排队等待执行。
			///
			/// @param task_func
			///
			std::shared_ptr<base::task::ITask> Run(std::function<void()> const &task_func);
		};

	} // namespace task
} // namespace base
