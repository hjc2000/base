#include "Size.h"
#include "base/string/define.h"
#include <stdexcept>

base::Size::Size(int32_t x, int32_t y)
{
	if (x < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "尺寸不能是负数。"};
	}

	if (y < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "尺寸不能是负数。"};
	}

	_x = x;
	_y = y;
}
