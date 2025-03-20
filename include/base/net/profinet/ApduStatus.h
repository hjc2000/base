#pragma once
#include "base/stream/Span.h"

namespace base
{
	namespace profinet
	{
		/// @brief 应用层协议数据单元的状态。
		class ApduStatus
		{
		private:
			base::Span _span;

		public:
			ApduStatus() = default;
			ApduStatus(base::Span const &span);

			base::Span const &Span() const;

			/// @brief 对循环周期的计数。
			/// @note 对于 RTC-PDU，循环周期是 31.25μs，本属性对循环周期计数。
			/// 接收方使用本属性来检验数据的时效性，以及判断是否重复或丢失。
			/// @return
			uint16_t CycleCounter() const;
			void SetCycleCounter(uint16_t value);

			/// @brief 数据状态。分成 8 个位使用，每个位都有含义。
			/// @return
			uint8_t DataStatus() const;
			void SetDataStatus(uint8_t value);

			/// @brief 传输状态。用来指示一些错误。
			/// @return
			uint8_t TransferStatus() const;
			void SetTransferStatus(uint8_t value);
		};
	} // namespace profinet
} // namespace base
