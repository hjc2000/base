#pragma once
#include <base/net/IPAddress.h>
#include <base/net/profinet/enum/ServiceTypeEnum.h>
#include <base/net/profinet/FidApdu.h>
#include <base/stream/MemoryStream.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP 请求帧中的服务 ID.
		enum class DcpServiceIdEnum : uint8_t
		{
			Get = 0x03,
			Set = 0x04,
			Identify = 0x05,
			Hello = 0x06,
		};

		class DcpHelloRequestPdu
		{
		private:
			base::profinet::FidApdu _fid_apdu;
			base::Span _this_span;
			base::AutoBitConverter _converter{std::endian::big};
			std::shared_ptr<base::MemoryStream> _block_stream;

#pragma region 私有属性设置函数
			void SetServiceId(base::profinet::DcpServiceIdEnum value);
			void SetServiceType(base::profinet::ServiceTypeEnum value);
			void SetDataLength(uint16_t value);
#pragma endregion

		public:
			/// @brief 构造函数。
			/// @param span 以太网的发送缓冲区。
			DcpHelloRequestPdu(base::Span const &span);

			/// @brief 源 MAC 地址。
			/// @return
			base::Mac SourceMac() const
			{
				return _fid_apdu.SourceMac();
			}

			/// @brief 设置源 MAC 地址。
			/// @param value
			void SetSourceMac(base::Mac const &value)
			{
				_fid_apdu.SetSourceMac(value);
			}

			base::profinet::DcpServiceIdEnum ServiceId() const;
			base::profinet::ServiceTypeEnum ServiceType() const;

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			/// @brief Blocks 的有效数据的长度。
			/// @return
			uint16_t DataLength() const;

			/// @brief 删除 Blocks 区域的所有块。
			void ClearAllBlocks();

			/// @brief 放置描述站点名称的块。
			/// @param station_name
			void PutNameOfStationBlock(std::string const &station_name);

			/// @brief 放置 IP 地址信息块。
			/// @param ip_not_set
			/// @param ip
			/// @param gateway
			/// @param netmask
			void PutIPAddressInfomationBlock(bool ip_not_set,
											 base::IPAddress const &ip,
											 base::IPAddress const &gateway,
											 base::IPAddress const &netmask);

			/// @brief 整个以太网帧缓冲区中的有效数据 span.
			/// @return
			base::Span ValidDataSpan() const
			{
				return _fid_apdu.ValidDataSpan();
			}
		};
	} // namespace profinet
} // namespace base
