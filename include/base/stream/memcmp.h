#pragma once
#include "base/string/define.h"
#include <bit>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <type_traits>

namespace base
{
	constexpr int32_t memcmp(void const *a, void const *b, int32_t size)
	{
		if (size < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "size 不能为负值。"};
		}

		if (!std::is_constant_evaluated())
		{
			return std::memcmp(a, b, size);
		}

		if (size == 0)
		{
			return 0;
		}

		if (a == b)
		{
			return 0;
		}

		uint8_t const *bufffer_a = std::bit_cast<uint8_t const *>(a);
		uint8_t const *bufffer_b = std::bit_cast<uint8_t const *>(b);

		for (int32_t i = 0; i < size; i++)
		{
			int32_t value_a = bufffer_a[i];
			int32_t value_b = bufffer_b[i];

			if (value_a != value_b)
			{
				return value_a - value_b;
			}
		}

		return 0;
	}

} // namespace base
