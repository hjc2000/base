#include "ThreadPool.h" // IWYU pragma: keep
#include "base/string/define.h"
#include "base/task/ThreadPool/TaskContext.h"
#include "base/task/ThreadPool/Worker.h"
#include <stdexcept>

base::task::ThreadPool::ThreadPool(int32_t thread_count)
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

void base::task::ThreadPool::Dispose()
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

std::shared_ptr<base::task::ITask> base::task::ThreadPool::Run(std::function<void()> const &task_func)
{
	if (_disposed)
	{
		throw base::ObjectDisposedException{};
	}

	std::shared_ptr<Task> task{new Task{task_func}};
	_task_queue.Enqueue(task);
	return task;
}
