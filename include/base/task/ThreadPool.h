#pragma once
#include "base/container/BlockingQueue.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "ITask.h"
#include "task.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

namespace base
{
	namespace task
	{
		class ThreadPool :
			base::IDisposable
		{
		private:
			/* #region Worker */

			class Worker :
				base::IDisposable
			{
			private:
				base::BlockingQueue<std::function<void()>> &_task_queue;
				std::shared_ptr<base::task::ITask> _task{};
				std::atomic_bool _disposed = false;

				void ThreadFunc()
				{
					while (true)
					{
						if (_disposed)
						{
							return;
						}

						std::function<void()> task_func = _task_queue.Dequeue();
						if (task_func == nullptr)
						{
							continue;
						}

						task_func();
					}
				}

			public:
				Worker(base::BlockingQueue<std::function<void()>> &task_queue)
					: _task_queue(task_queue)
				{
					_task = base::task::run([this]()
											{
												ThreadFunc();
											});
				}

				~Worker()
				{
					Dispose();
				}

				///
				/// @brief 主动释放对象，让对象不再能够工作。
				///
				///
				virtual void Dispose() override
				{
					if (_disposed)
					{
						return;
					}

					_disposed = true;
					_task->Wait();
				}

			}; // class Worker

			/* #endregion */

			int32_t _thread_count = 1;
			std::vector<std::shared_ptr<Worker>> _workers;
			base::BlockingQueue<std::function<void()>> _task_queue;
			std::atomic_bool _disposed = false;

		public:
			ThreadPool(int32_t thread_count)
				: _task_queue(thread_count)
			{
				if (thread_count <= 0)
				{
					throw std::invalid_argument{CODE_POS_STR + "线程数必须大于 0."};
				}

				_thread_count = thread_count;
				for (int32_t i = 0; i < _thread_count; i++)
				{
					_workers.push_back(std::shared_ptr<Worker>{new Worker{_task_queue}});
				}
			}

			~ThreadPool()
			{
				Dispose();
			}

			///
			/// @brief 主动释放对象，让对象不再能够工作。
			///
			///
			virtual void Dispose() override
			{
				if (_disposed)
				{
					return;
				}

				_disposed = true;

				// 先释放队列，让其不再具有阻塞能力。
				_task_queue.Dispose();

				for (auto &worker : _workers)
				{
					worker->Dispose();
				}
			}

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
			void Run(std::function<void()> const &task_func)
			{
				if (_disposed)
				{
					throw base::ObjectDisposedException{};
				}

				_task_queue.Enqueue(task_func);
			}
		};

	} // namespace task
} // namespace base
