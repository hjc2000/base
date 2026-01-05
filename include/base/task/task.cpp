#include "task.h"
#include "base/string/define.h"
#include "base/task/TaskCompletionSignal.h"
#include <exception>
#include <iostream>
#include <thread>

#if HAS_THREAD

std::shared_ptr<base::task::ITask> base::task::run(std::function<void()> const &func)
{
	std::shared_ptr<base::task::TaskCompletionSignal> signal{new base::task::TaskCompletionSignal{false}};

	// 捕获所有异常，输出错误消息
	auto safe_func = [func, signal]()
	{
		try
		{
			func();
		}
		catch (std::exception const &e)
		{
			std::cerr << CODE_POS_STR
					  << "后台线程发生异常。异常消息："
					  << e.what()
					  << std::endl;
		}
		catch (...)
		{
			std::cerr << CODE_POS_STR
					  << "后台线程发生未知异常。"
					  << std::endl;
		}

		signal->SetResult();
	};

	std::thread{safe_func}.detach();
	return signal;
}

#endif
