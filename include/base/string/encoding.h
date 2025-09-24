#pragma once
#include "base/bit/bit_converte.h"
#include <bit>
#include <cstddef>
#include <cstdint>
#include <string>

namespace base
{
	namespace string
	{
		namespace encoding
		{
			constexpr std::u16string to_utf16le_string(std::u16string const &str)
			{
				if (std::endian::native == std::endian::little)
				{
					return str;
				}

				std::u16string ret{str};
				for (size_t i = 0; i < ret.size(); i++)
				{
					uint8_t high = ret[i] >> 8;
					uint8_t low = ret[i] & 0xFF;

					// 颠倒字节序。
					uint16_t value = base::bit_converte::ToUInt16(low, high);
					ret[i] = value;
				}

				return ret;
			}

		} // namespace encoding
	} // namespace string
} // namespace base
