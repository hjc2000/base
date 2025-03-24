#include "task.h"
#include "base/string/define.h"
#include <exception>
#include <iostream>
#include <thread>

#if HAS_THREAD

void base::task::Run(std::function<void()> func)
{
	// 捕获所有异常，输出错误消息
	auto safe_func = [func]()
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
	};

	std::thread{safe_func}.detach();
}

#endif
