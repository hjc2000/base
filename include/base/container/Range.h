#pragma once
#include <cstdint>

namespace base
{
	///
	/// @brief 表示范围。是个左闭右开区间。
	///
	class Range
	{
	private:
		int64_t _begin = 0;
		int64_t _end = 0;

	public:
		constexpr Range() = default;

		///
		/// @brief 构造函数。
		///
		/// @param begin 区间左端点。是闭的。
		/// @param end 区间右端点。是开的。
		///
		constexpr Range(int64_t begin, int64_t end)
			: _begin(begin),
			  _end(end)
		{
		}

		///
		/// @brief 区间左端点。区间左边是闭的。
		///
		/// @return
		///
		constexpr int64_t Begin() const
		{
			return _begin;
		}

		///
		/// @brief 区间右端点。区间右边是开的。
		///
		/// @return
		///
		constexpr int64_t End() const
		{
			return _end;
		}

		///
		/// @brief End - Begin，等于这个区间的大小。
		///
		/// @return
		///
		constexpr int64_t Size() const
		{
			return _end - _begin;
		}
	};

} // namespace base
