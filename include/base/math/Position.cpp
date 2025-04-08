#include "Position.h"
#include <array>
#include <cstdint>

base::Position::Position(int64_t x, int64_t y)
	: _x(x),
	  _y(y)
{
}

/* #region 比较运算符 */

bool base::Position::operator==(base::Position const &another) const
{
	std::array<int64_t, 2> arr{_x, _y};
	std::array<int64_t, 2> another_arr{another._x, another._y};
	return arr == another_arr;
}

bool base::Position::operator<(base::Position const &another) const
{
	std::array<int64_t, 2> arr{_x, _y};
	std::array<int64_t, 2> another_arr{another._x, another._y};
	return arr < another_arr;
}

bool base::Position::operator>(base::Position const &another) const
{
	std::array<int64_t, 2> arr{_x, _y};
	std::array<int64_t, 2> another_arr{another._x, another._y};
	return arr > another_arr;
}

bool base::Position::operator<=(base::Position const &another) const
{
	std::array<int64_t, 2> arr{_x, _y};
	std::array<int64_t, 2> another_arr{another._x, another._y};
	return arr <= another_arr;
}

bool base::Position::operator>=(base::Position const &another) const
{
	std::array<int64_t, 2> arr{_x, _y};
	std::array<int64_t, 2> another_arr{another._x, another._y};
	return arr >= another_arr;
}

/* #endregion */
