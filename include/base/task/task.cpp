#include "task.h"
#include "base/string/define.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <thread>

#if HAS_THREAD

int64_t base::task::DefaultTaskStackSize()
{
	throw std::runtime_error{CODE_POS_STR + "通用操作系统平台不需要这个。"};
}

void base::task::SetDefaultTaskStackSize(int64_t value)
{
	throw std::runtime_error{CODE_POS_STR + "通用操作系统平台不需要这个。"};
}

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

void base::task::Run(std::function<void()> func, int64_t stack_size)
{
	Run(func);
}

#endif
