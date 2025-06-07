#pragma once
#include "base/container/Range.h"
#include "base/net/profidrive/data-type/N4.h"
#include "base/net/profidrive/data-type/V2.h"
#include "base/net/profidrive/telegram/ReceivedTelegram3.h"
#include "base/stream/Span.h"

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
			void Write_G1_XIST1(base::profidrive::N4 const &value)
			{
				value.GetBytes(_span[base::Range{10, 14}]);
			}

			///
			/// @brief 向内存段写入 G1_XIST2.
			///
			/// @param value
			///
			void Write_G1_XIST2(base::profidrive::N4 const &value)
			{
				value.GetBytes(_span[base::Range{14, 18}]);
			}

			///
			/// @brief 向内存段写入整个 ReceivedTelegram3.
			///
			/// @param value
			///
			void Write(base::profidrive::ReceivedTelegram3 const &value)
			{
				Write_ZSW1(value.ZSW1());
				Write_NIST_B(value.NIST_B());
				Write_ZSW2(value.ZSW2());
				Write_G1_ZSW(value.G1_ZSW());
				Write_G1_XIST1(value.G1_XIST1());
				Write_G1_XIST2(value.G1_XIST2());
			}
		};

	} // namespace profidrive
} // namespace base
