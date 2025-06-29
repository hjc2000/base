#pragma once
#include "base/task/task.h"
#include "base/task/ThreadPool.h"
#include "base/task/ThreadPool/TaskContext.h"

class base::task::ThreadPool::Worker final :
	base::IDisposable
{
private:
	base::BlockingQueue<std::shared_ptr<Task>> &_task_queue;
	std::shared_ptr<base::task::ITask> _task{};
	std::atomic_bool _disposed = false;

	void ThreadFunc();

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
};
