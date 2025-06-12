#pragma once
#include <cstdint>

namespace base
{
	constexpr int64_t ceil(double value)
	{
		int64_t int_part = static_cast<int64_t>(value);
		double fractional_part = value - static_cast<double>(int_part);
		if (fractional_part == 0.0)
		{
			return int_part;
		}

		return int_part + 1;
	}

} // namespace base
