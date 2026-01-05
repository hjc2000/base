#pragma once
#include "base/net/profinet/ApduStatus.h"
#include "base/net/profinet/C_SDU.h"
#include "base/stream/Span.h"

namespace base::profinet
{
	///
	/// @brief 实时循环帧的协议数据单元。
	///
	class RtcPdu
	{
	private:
		base::Span _span;

	public:
		RtcPdu() = default;

		RtcPdu(base::Span const &span)
		{
			_span = span;
		}

		base::Span const &Span() const
		{
			return _span;
		}

		base::profinet::C_SDU C_SDU() const
		{
			return base::profinet::C_SDU();
		}

		void Set_C_SDU(base::profinet::C_SDU const &value)
		{
			C_SDU().Span().CopyFrom(value.Span());
		}

		base::profinet::ApduStatus ApduStatus() const
		{
			return base::profinet::ApduStatus();
		}

		void SetApduStatus(base::profinet::ApduStatus const &value)
		{
			ApduStatus().Span().CopyFrom(value.Span());
		}
	};

} // namespace base::profinet
