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
		/// @brief 构造函数。
		/// @param begin 区间左端点。是闭的。
		/// @param end 区间右端点。是开的。
		Range(int32_t begin, int32_t end)
			: _begin(begin),
			  _end(end)
		{
		}

		/// @brief 区间左端点。区间左边是闭的。
		/// @return
		int32_t Begin() const
		{
			return _begin;
		}

		/// @brief 区间右端点。区间右边是开的。
		/// @return
		int32_t End() const
		{
			return _end;
		}

		/// @brief End - Begin，等于这个区间的大小。
		/// @return
		int32_t Size() const
		{
			return _end - _begin;
		}
	};
} // namespace base
