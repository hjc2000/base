#include "Worker.h"
#include "base/Console.h"
#include "base/IDisposable.h"
#include "base/task/ThreadPool/Task.h"
#include <stdexcept>

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
