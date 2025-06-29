#include "Worker.h"
#include "base/task/ThreadPool/Task.h"

void base::task::ThreadPool::Worker::ThreadFunc()
{
	while (true)
	{
		try
		{
			if (_disposed)
			{
				return;
			}

			std::shared_ptr<Task> task = _task_queue.Dequeue();
			if (task == nullptr)
			{
				continue;
			}

			(*task)();
		}
		catch (...)
		{
		}
	}
}
