#pragma once
#include "base/profidrive/data-type/N4.h"
#include "base/profidrive/data-type/V2.h"
#include "base/profidrive/telegram/SentTelegram3.h"
#include "base/stream/Span.h"

namespace base::profidrive
{
	class SentTelegram3Writer
	{
	private:
		base::Span _span{};

	public:
		SentTelegram3Writer(base::Span const &span);

		///
		/// @brief 向内存段写入 STW1.
		///
		/// @param value
		///
		void Write_STW1(base::profidrive::V2 const &value)
		{
			value.GetBytes(_span[base::Range{0, 2}]);
		}

		///
		/// @brief 向内存段写入 NSOLL_B.
		///
		/// @param value
		///
		void Write_NSOLL_B(base::profidrive::N4 const &value)
		{
			value.GetBytes(_span[base::Range{2, 6}]);
		}

		///
		/// @brief 向内存段写入 STW2.
		///
		/// @param value
		///
		void Write_STW2(base::profidrive::V2 const &value)
		{
			value.GetBytes(_span[base::Range{6, 8}]);
		}

		///
		/// @brief 向内存段写入 G1_STW.
		///
		/// @param value
		///
		void Write_G1_STW(base::profidrive::V2 const &value)
		{
			value.GetBytes(_span[base::Range{8, 10}]);
		}

		///
		/// @brief 向内存段写入整个报文 3.
		///
		/// @param value
		///
		void Write(base::profidrive::SentTelegram3 const &value);
	};

} // namespace base::profidrive
