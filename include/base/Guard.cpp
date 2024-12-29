#include "Guard.h"
#include <base/string/define.h>
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
	catch (...)
	{
	}
}
