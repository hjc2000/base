#pragma once
#include <cstdint>
#include <limits>

namespace base
{
	namespace random
	{
		/**
		 * @brief 生成指定范围内的 int64_t 的随机数。
		 *
		 * @param min
		 * @param max
		 * @return int64_t
		 */
		int64_t GenerateInt64Random(int64_t min = std::numeric_limits<int64_t>::min(),
									int64_t max = std::numeric_limits<int64_t>::max());
	} // namespace random
} // namespace base
