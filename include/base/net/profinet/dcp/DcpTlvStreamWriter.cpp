#include "DcpTlvStreamWriter.h"
#include "base/bit/AutoBitConverter.h"
#include "base/string/define.h"

void base::profinet::DcpTlvStreamWriter::WriteBlockHeader(uint8_t option,
														  uint8_t suboption,
														  uint16_t block_length,
														  uint16_t block_info)
{
	_stream.Write(&option, 0, 1);
	_stream.Write(&suboption, 0, 1);
	base::big_endian_remote_converter.GetBytes(block_length, _stream);
	base::big_endian_remote_converter.GetBytes(block_info, _stream);
}

base::profinet::DcpTlvStreamWriter::DcpTlvStreamWriter(base::Stream &stream)
	: _stream(stream)
{
}

void base::profinet::DcpTlvStreamWriter::WriteNameOfStationBlock(std::string const &station_name)
{
	WriteBlockHeader(2,
					 2,
					 // 2 字节的 block_infos 加上实际的名称长度。
					 2 + station_name.size(),
					 // 保留。始终为 0.
					 0);

	// Block 载荷
	{
		// 将名称字符串写入流
		_stream.Write(reinterpret_cast<uint8_t const *>(station_name.data()),
					  0,
					  station_name.size());

		// 名称如果没有 2 字节对齐，需要填充。
		if (station_name.size() % 2 != 0)
		{
			uint8_t const padding = 0;
			_stream.Write(&padding, 0, 1);
		}
	}
}

void base::profinet::DcpTlvStreamWriter::WriteIPAddressInfomationBlock(bool ip_not_set,
																	   base::IPAddress const &ip,
																	   base::IPAddress const &gateway,
																	   base::IPAddress const &netmask)
{
	WriteBlockHeader(1,
					 2,
					 /**
					  * IP 地址，网关，子网掩码，共 3 个 IP 地址，有 3 * 4 = 12 字节。
					  * 还有 2 字节的 block_info.
					  */
					 2 + 3 * 4,
					 ip_not_set ? 1 : 0);

	// Block 载荷
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(ip.Span());
		ip_buffer_span.Reverse();
		_stream.Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(netmask.Span());
		ip_buffer_span.Reverse();
		_stream.Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(gateway.Span());
		ip_buffer_span.Reverse();
		_stream.Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}
}

void base::profinet::DcpTlvStreamWriter::WriteIdBlock(uint16_t vendor_id, uint16_t device_id)
{
	WriteBlockHeader(2,
					 3,
					 6,
					 0);

	// Block 载荷
	{
		base::big_endian_remote_converter.GetBytes(vendor_id, _stream);
		base::big_endian_remote_converter.GetBytes(device_id, _stream);
	}
}

void base::profinet::DcpTlvStreamWriter::WriteOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id)
{
	WriteBlockHeader(2,
					 8,
					 6,
					 0);

	// Block 载荷
	{
		base::big_endian_remote_converter.GetBytes(oem_vendor_id, _stream);
		base::big_endian_remote_converter.GetBytes(oem_device_id, _stream);
	}
}

void base::profinet::DcpTlvStreamWriter::WriteDeviceInitiativeBlock(bool hello)
{
	WriteBlockHeader(6,
					 1,
					 4,
					 0);

	// Block 载荷
	{
		uint16_t value = hello ? 1 : 0;
		base::big_endian_remote_converter.GetBytes(value, _stream);
	}
}
