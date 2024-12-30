#pragma once
#include <base/net/profinet/enum/ServiceIdEnum.h>
#include <base/net/profinet/enum/ServiceTypeEnum.h>
#include <base/net/profinet/FidApdu.h>
#include <base/stream/MemoryStream.h>

namespace base
{
	namespace profinet
	{
		class DcpHelloRequestPdu
		{
		private:
			base::profinet::FidApdu _fid_apdu;
			base::Span _this_span;
			base::AutoBitConverter _converter{std::endian::big};
			std::shared_ptr<base::MemoryStream> _block_stream;

#pragma region 私有属性设置函数
			void SetServiceId(base::profinet::ServiceIdEnum value);
			void SetServiceType(base::profinet::ServiceTypeEnum value);
			void SetDataLength(uint16_t value);
#pragma endregion

		public:
			/// @brief 构造函数。
			/// @param span 以太网的发送缓冲区。
			DcpHelloRequestPdu(base::Span const &span);

			base::profinet::ServiceIdEnum ServiceId() const;
			base::profinet::ServiceTypeEnum ServiceType() const;

			uint32_t Xid() const;
			void SetXid(uint32_t value);

			/// @brief Blocks 的有效数据的长度。
			/// @return
			uint16_t DataLength() const;

			/// @brief 用来放置各种块的区域。其中有效数据的长度为：DataLength.
			/// @return
			base::Span Blocks() const;

			/// @brief 删除 Blocks 区域的所有块。
			void ClearAllBlocks();

			/// @brief 放置描述站点名称的块。
			/// @param station_name
			void PutNameOfStationBlock(std::string const &station_name);

			base::ethernet::EthernetFrame &EthernetFrame()
			{
				return _fid_apdu.EthernetFrame();
			}
		};
	} // namespace profinet
} // namespace base
