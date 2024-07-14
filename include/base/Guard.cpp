#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include "Guard.h"
#include <stdexcept>

#if HAS_THREAD
#include <base/string/define.h>
#include <iostream>
#endif

base::Guard::Guard(std::function<void()> func)
{
	_func = func;
}

base::Guard::~Guard()
{
	try
	{
		if (_func)
		{
			_func();
		}
	}
#if HAS_THREAD
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR << "Guard 在析构中执行回调遇到异常 " << e.what() << std::endl;
	}
#endif
	catch (...)
	{
	}
}
