#pragma once
#include <stdint.h>

namespace base
{
	/// @brief 表示范围。是个左闭右开区间。
	class Range
	{
	private:
		int32_t _begin = 0;
		int32_t _end = 0;

	public:
		Range(int32_t begin, int32_t end)
			: _begin(begin),
			  _end(end)
		{
		}

		int32_t Begin() const
		{
			return _begin;
		}

		int32_t End() const
		{
			return _end;
		}

		int32_t Size() const
		{
			return _end - _begin;
		}
	};
} // namespace base
