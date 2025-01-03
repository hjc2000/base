#include "DcpHelloRequestWriter.h"
#include <base/string/define.h>

#pragma region 私有属性设置函数

void base::profinet::DcpHelloRequestWriter::SetServiceId(base::profinet::DcpServiceIdEnum value)
{
	_this_span[0] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestWriter::SetServiceType(base::profinet::DcpServiceTypeEnum value)
{
	_this_span[1] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequestWriter::SetDataLength(uint16_t value)
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	_converter.GetBytes(value, span);
}

void base::profinet::DcpHelloRequestWriter::UpdateSize()
{
	SetDataLength(_block_stream->Length());

	// 头部长度 10 字节加上 Blocks 的长度。
	_fid_apdu.SetValidPayloadSize(10 + DataLength());
}

#pragma endregion

base::profinet::DcpHelloRequestWriter::DcpHelloRequestWriter(base::Span const &span)
	: _fid_apdu(span)
{
	_fid_apdu.SetFrameId(base::profinet::FrameIdEnum::DcpHelloRequest);

	_fid_apdu.SetDestinationMac(base::Mac{
		std::endian::big,
		base::Array<uint8_t, 6>{
			0x01,
			0x0e,
			0xcf,
			0x00,
			0x00,
			0x01,
		},
	});

	_this_span = _fid_apdu.Payload();
	SetServiceId(base::profinet::DcpServiceIdEnum::Hello);
	SetServiceType(base::profinet::DcpServiceTypeEnum::Request);

	base::Span block_span = _this_span.Slice(base::Range{10, _this_span.Size()});
	_block_stream = std::shared_ptr<base::MemoryStream>{new base::MemoryStream{block_span}};
}

#pragma region DCP 头部

base::profinet::DcpServiceIdEnum base::profinet::DcpHelloRequestWriter::ServiceId() const
{
	return static_cast<base::profinet::DcpServiceIdEnum>(_this_span[0]);
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHelloRequestWriter::ServiceType() const
{
	return static_cast<base::profinet::DcpServiceTypeEnum>(_this_span[1]);
}

uint32_t base::profinet::DcpHelloRequestWriter::Xid() const
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHelloRequestWriter::SetXid(uint32_t value)
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHelloRequestWriter::DataLength() const
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	return _converter.ToUInt16(span);
}

#pragma endregion

#pragma region Blocks

void base::profinet::DcpHelloRequestWriter::ClearAllBlocks()
{
	SetDataLength(0);
	_block_stream->Clear();

	// Blocks 区的有效数据长度为 0，只剩下头部的 10 字节是有效数据。
	_fid_apdu.SetValidPayloadSize(10);
}

void base::profinet::DcpHelloRequestWriter::PutNameOfStationBlock(std::string const &station_name)
{
	// Block 头部
	{
		uint8_t option = 2;
		_block_stream->Write(&option, 0, 1);

		uint8_t suboption = 2;
		_block_stream->Write(&suboption, 0, 1);

		// 2 字节的 block_infos 加上实际的名称长度。
		uint16_t dcp_block_length = 2 + station_name.size();
		_converter.GetBytes(dcp_block_length, *_block_stream);

		// 保留。始终为 0.
		uint16_t block_info = 0;
		_converter.GetBytes(block_info, *_block_stream);
	}

	// Block 载荷
	{
		// 将名称字符串写入流
		_block_stream->Write(reinterpret_cast<uint8_t const *>(station_name.data()),
							 0,
							 station_name.size());

		// 名称如果没有 2 字节对齐，需要填充。
		if (station_name.size() % 2 != 0)
		{
			uint8_t padding = 0;
			_block_stream->Write(&padding, 0, 1);
		}
	}

	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutIPAddressInfomationBlock(bool ip_not_set,
																		base::IPAddress const &ip,
																		base::IPAddress const &gateway,
																		base::IPAddress const &netmask)
{
	// Block 头部
	{
		uint8_t option = 1;
		_block_stream->Write(&option, 0, 1);

		uint8_t suboption = 2;
		_block_stream->Write(&suboption, 0, 1);

		/**
		 * IP 地址，网关，子网掩码，共 3 个 IP 地址，有 3*4=12 字节。
		 * 还有 2 字节的 block_info.
		 */
		uint16_t const dcp_block_length = 2 + 3 * 4;
		_converter.GetBytes(dcp_block_length, *_block_stream);

		uint16_t block_info = ip_not_set ? 1 : 0;
		_converter.GetBytes(block_info, *_block_stream);
	}

	// Block 载荷
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(ip.AsReadOnlySpan());
		ip_buffer_span.Reverse();
		_block_stream->Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(netmask.AsReadOnlySpan());
		ip_buffer_span.Reverse();
		_block_stream->Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}
	{
		if (ip.Type() != base::IPAddressType::IPV4)
		{
			throw std::invalid_argument{CODE_POS_STR + "必须是 IPV4 地址。"};
		}

		uint8_t ip_buffer[4];
		base::Span ip_buffer_span{ip_buffer, sizeof(ip_buffer)};
		ip_buffer_span.CopyFrom(gateway.AsReadOnlySpan());
		ip_buffer_span.Reverse();
		_block_stream->Write(ip_buffer_span.Buffer(), 0, ip_buffer_span.Size());
	}

	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutIdBlock(uint16_t vendor_id, uint16_t device_id)
{
	// Block 头部
	{
		uint8_t const option = 2;
		_block_stream->Write(&option, 0, 1);

		uint8_t const suboption = 3;
		_block_stream->Write(&suboption, 0, 1);

		uint16_t const dcp_block_length = 6;
		_converter.GetBytes(dcp_block_length, *_block_stream);

		uint16_t const block_info = 0;
		_converter.GetBytes(block_info, *_block_stream);
	}

	// Block 载荷
	{
		_converter.GetBytes(vendor_id, *_block_stream);
		_converter.GetBytes(device_id, *_block_stream);
	}

	UpdateSize();
}

void base::profinet::DcpHelloRequestWriter::PutOemIdBlock(uint16_t oem_vendor_id, uint16_t oem_device_id)
{
	// Block 头部
	{
		uint8_t const option = 2;
		_block_stream->Write(&option, 0, 1);

		uint8_t const suboption = 8;
		_block_stream->Write(&suboption, 0, 1);

		uint16_t const dcp_block_length = 6;
		_converter.GetBytes(dcp_block_length, *_block_stream);

		uint16_t const block_info = 0;
		_converter.GetBytes(block_info, *_block_stream);
	}

	// Block 载荷
	{
		_converter.GetBytes(oem_vendor_id, *_block_stream);
		_converter.GetBytes(oem_device_id, *_block_stream);
	}

	UpdateSize();
}

#pragma endregion
