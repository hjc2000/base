#pragma once
#include "base/net/IPAddress.h"
#include "base/stream/Stream.h"

namespace base::profinet
{
	///
	/// @brief DCP 的 Block 是 TLV 格式。即：类型、长度、值。本类专门用来向流中写入 TLV.
	///
	class DcpTlvStreamWriter
	{
	private:
		base::Stream &_stream;

		///
		/// @brief 将块的头部写入 _stream.
		///
		/// @param option 块的选项。
		/// @param suboption 块的子选项。
		/// @param block_length 当前块的载荷长度（不包括块头部本身）。
		/// @param block_info 块信息。
		///
		void WriteBlockHeader(uint8_t option, uint8_t suboption, uint16_t block_length, uint16_t block_info);

	public:
		DcpTlvStreamWriter(base::Stream &stream);

		///
		/// @brief 写入描述站点名称的块。
		///
		/// @param station_name
		///
		void WriteNameOfStationBlock(std::string const &station_name);

		///
		/// @brief 写入 IP 地址信息块。
		///
		/// @param ip_not_set
		/// @param ip
		/// @param gateway
		/// @param netmask
		///
		void WriteIPAddressInfomationBlock(bool ip_not_set,
										   base::IPAddress const &ip,
										   base::IPAddress const &gateway,
										   base::IPAddress const &netmask);

		void WriteIdBlock(uint16_t vendor_id, uint16_t device_id);

		void WriteOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id);

		///
		/// @brief 写入 “设备主动性” 块。
		///
		/// @param hello 设备是否会在上电后主动发送 DCP-Hllo.
		///
		void WriteDeviceInitiativeBlock(bool hello);
	};

} // namespace base::profinet
