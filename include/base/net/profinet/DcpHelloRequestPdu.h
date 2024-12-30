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

		public:
			DcpHelloRequestPdu() = default;
			DcpHelloRequestPdu(base::profinet::FidApdu const &fid_apdu);

			base::Span Span() const;

			/// @brief 配置下层的 FidApdu.
			void ConfigureLowlayer();

			ServiceIdEnum ServiceId() const;
			void SetServiceId(ServiceIdEnum value);

			ServiceTypeEnum ServiceType() const;
			void SetServiceType(ServiceTypeEnum value);

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			/// @brief 传输延迟系数。
			/// @note 在 DCP HELLO 请求中本属性无用。标准文件中将此时的 DCP 头部叫作 DCP-UC-Header，
			/// 本属性被描述为 Padding，即填充，应该使用 0 填充。
			/// @return
			uint16_t ResponseDelayFactor() const;
			void SetResponseDelayFactor(uint16_t value);

			uint16_t DataLength() const;
			void SetDataLength(uint16_t value);

			base::profinet::NameOfStationBlockRes NameOfStationBlockRes() const;
			void SetNameOfStationBlockRes(base::profinet::NameOfStationBlockRes const &value);
		};
	} // namespace profinet
} // namespace base
