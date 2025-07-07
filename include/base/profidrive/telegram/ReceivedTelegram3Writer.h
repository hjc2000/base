#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Range.h"
#include "base/profidrive/data-type/N4.h"
#include "base/profidrive/data-type/V2.h"
#include "base/profidrive/telegram/ReceivedTelegram3.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base
{
	namespace profidrive
	{
		class ReceivedTelegram3Writer
		{
		private:
			base::Span _span{};

		public:
			ReceivedTelegram3Writer(base::Span const &span);

			///
			/// @brief 向内存段写入 ZSW1.
			///
			/// @param value
			///
			void Write_ZSW1(base::profidrive::V2 const &value)
			{
				value.GetBytes(_span[base::Range{0, 2}]);
			}

			///
			/// @brief 向内存段写入 NIST_B.
			///
			/// @param value
			///
			void Write_NIST_B(base::profidrive::N4 const &value)
			{
				value.GetBytes(_span[base::Range{2, 6}]);
			}

			///
			/// @brief 向内存段写入 ZSW2.
			///
			/// @param value
			///
			void Write_ZSW2(base::profidrive::V2 const &value)
			{
				value.GetBytes(_span[base::Range{6, 8}]);
			}

			///
			/// @brief 向内存段写入 G1_ZSW.
			///
			/// @param value
			///
			void Write_G1_ZSW(base::profidrive::V2 const &value)
			{
				value.GetBytes(_span[base::Range{8, 10}]);
			}

			///
			/// @brief 向内存段写入 G1_XIST1.
			///
			/// @param value
			///
			void Write_G1_XIST1(uint32_t value)
			{
				base::Span span = _span[base::Range{10, 14}];
				base::big_endian_remote_converter.GetBytes(value, span);
			}

			///
			/// @brief 向内存段写入 G1_XIST2.
			///
			/// @param value
			///
			void Write_G1_XIST2(uint32_t value)
			{
				base::Span span = _span[base::Range{14, 18}];
				base::big_endian_remote_converter.GetBytes(value, span);
			}

			///
			/// @brief 向内存段写入整个 ReceivedTelegram3.
			///
			/// @param value
			///
			void Write(base::profidrive::ReceivedTelegram3 const &value);
		};

	} // namespace profidrive
} // namespace base
