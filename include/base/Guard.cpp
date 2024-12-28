#include "Guard.h"
#include <base/string/define.h>
#include <iostream>
#include <stdexcept>

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
	catch (std::exception const &e)
	{
		std::cerr << CODE_POS_STR << "Guard 在析构中执行回调遇到异常 " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << CODE_POS_STR << "Guard 在析构中执行回调遇到未知异常" << std::endl;
	}
}
