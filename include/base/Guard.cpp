#include "Guard.h"

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
