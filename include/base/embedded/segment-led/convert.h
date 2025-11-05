#pragma once
#include "base/bit/bit.h"
#include "base/string/define.h"
#include "base/ui/LedSegmentSymbol.h"
#include <stdexcept>

namespace base::segment_led
{
	constexpr base::ui::LedSegmentSymbol symbol_code_to_enum(uint8_t symbol_code)
	{
		switch (symbol_code)
		{
		case 0:
			{
				return base::ui::LedSegmentSymbol::Space;
			}
		case base::bit::Bit(4) |
			base::bit::Bit(5):
			{
				return base::ui::LedSegmentSymbol::Number_1;
			}
		case base::bit::Bit(0) |
			base::bit::Bit(5) |
			base::bit::Bit(6) |
			base::bit::Bit(2) |
			base::bit::Bit(3):
			{
				return base::ui::LedSegmentSymbol::Number_2;
			}
		case base::bit::Bit(0) |
			base::bit::Bit(5) |
			base::bit::Bit(6) |
			base::bit::Bit(4) |
			base::bit::Bit(3):
			{
				return base::ui::LedSegmentSymbol::Number_3;
			}
		case base::bit::Bit(1) |
			base::bit::Bit(5) |
			base::bit::Bit(6) |
			base::bit::Bit(4):
			{
				return base::ui::LedSegmentSymbol::Number_4;
			}
		default:
			{
				throw std::invalid_argument{CODE_POS_STR + "非法参数。"};
			}
		}
	}

} // namespace base::segment_led
