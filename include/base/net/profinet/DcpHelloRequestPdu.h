#pragma once
#include <base/net/profinet/enum/ServiceIdEnum.h>
#include <base/net/profinet/enum/ServiceTypeEnum.h>
#include <base/net/profinet/FidApdu.h>
#include <base/net/profinet/NameOfStationBlockRes.h>

namespace base
{
	namespace profinet
	{
		class DcpHelloRequestPdu
		{
		private:
			base::profinet::FidApdu _fid_apdu;
			base::Span _this_span;

			void SetServiceId(base::profinet::ServiceIdEnum value);
			void SetServiceType(base::profinet::ServiceTypeEnum value);
			void SetDataLength(uint16_t value);

		public:
			/// @brief 构造函数。
			/// @param span 以太网的发送缓冲区。
			DcpHelloRequestPdu(base::Span const &span);

			base::profinet::ServiceIdEnum ServiceId() const;

			base::profinet::ServiceTypeEnum ServiceType() const;

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			uint16_t DataLength() const;

			base::profinet::NameOfStationBlockRes NameOfStationBlockRes() const;
			void SetNameOfStationBlockRes(base::profinet::NameOfStationBlockRes const &value);
		};
	} // namespace profinet
} // namespace base
