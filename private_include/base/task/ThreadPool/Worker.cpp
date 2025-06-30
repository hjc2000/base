#include "Worker.h"
#include "base/Console.h"
#include "base/IDisposable.h"
#include "base/task/ThreadPool/Task.h"

void base::task::ThreadPool::Worker::ThreadFunc()
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
		catch (base::ObjectDisposedException const &e)
		{
			return;
		}
		catch (std::exception const &e)
		{
			base::console.WriteErrorLine(CODE_POS_STR + e.what());
			return;
		}
		catch (...)
		{
			base::console.WriteErrorLine(CODE_POS_STR + "未知异常。");
			return;
		}

		if (task == nullptr)
		{
			continue;
		}

		(*task)();
	}
}
