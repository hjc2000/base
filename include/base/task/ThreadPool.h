#pragma once
#include "base/Console.h"
#include "base/container/BlockingQueue.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/task.h"
#include "base/task/TaskCompletionSignal.h"
#include "ITask.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

namespace base::task
{
	class ThreadPool final :
		base::IDisposable
	{
	private:
		class Task final :
			public base::task::ITask
		{
		private:
			std::function<void()> _func{};
			base::task::TaskCompletionSignal _signal{false};

		public:
			Task(std::function<void()> const &func)
				: _func(func)
			{
			}

			void operator()() noexcept
			{
				base::task::TaskCompletionSignalGuard g{_signal};
				if (_func == nullptr)
				{
					return;
				}

				try
				{
					_func();
				}
				catch (std::exception const &e)
				{
					base::console().WriteError(CODE_POS_STR + e.what());
				}
				catch (...)
				{
					base::console().WriteError(CODE_POS_STR + "未知异常。");
				}
			}

			///
			/// @brief 任务已经完成。
			///
			/// @return 已完成会返回 true，否则返回 false.
			///
			virtual bool IsCompleted() const override
			{
				return _signal.IsCompleted();
			}

			///
			/// @brief 等待任务完成。会阻塞当前线程。
			///
			///
			virtual void Wait() override
			{
				_signal.Wait();
			}

		}; // class Task

		class Worker final :
			base::IDisposable
		{
		private:
			base::BlockingQueue<std::shared_ptr<Task>> &_task_queue;
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

					std::shared_ptr<Task> task;

					try
					{
						task = _task_queue.Dequeue();
					}
					catch (std::underflow_error const &e)
					{
						// _task_queue 是个阻塞队列，退队引发这个异常说明 _task_queue 已经被处置了，
						// 此时线程应该退出。
						return;
					}
					catch (base::ObjectDisposedException const &e)
					{
						return;
					}
					catch (std::exception const &e)
					{
						base::console().WriteErrorLine(CODE_POS_STR + e.what());
						return;
					}
					catch (...)
					{
						base::console().WriteErrorLine(CODE_POS_STR + "未知异常。");
						return;
					}

					if (task == nullptr)
					{
						continue;
					}

					// Task 的 () 运算符不会抛出异常。
					(*task)();
				}
			}

		public:
			Worker(base::BlockingQueue<std::shared_ptr<Task>> &task_queue)
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

		int32_t _thread_count = 1;
		std::vector<std::shared_ptr<Worker>> _workers;
		base::BlockingQueue<std::shared_ptr<Task>> _task_queue;
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
		std::shared_ptr<base::task::ITask> Run(std::function<void()> const &task_func)
		{
			if (_disposed)
			{
				throw base::ObjectDisposedException{};
			}

			std::shared_ptr<Task> task{new Task{task_func}};
			_task_queue.Enqueue(task);
			return task;
		}
	};

} // namespace base::task
