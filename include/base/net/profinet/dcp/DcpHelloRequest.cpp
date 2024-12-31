#include "DcpHelloRequest.h"
#include <base/string/define.h>

#pragma region 私有属性设置函数

void base::profinet::DcpHelloRequest::SetServiceId(base::profinet::DcpServiceIdEnum value)
{
	_this_span[0] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequest::SetServiceType(base::profinet::DcpServiceTypeEnum value)
{
	_this_span[1] = static_cast<uint8_t>(value);
}

void base::profinet::DcpHelloRequest::SetDataLength(uint16_t value)
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	_converter.GetBytes(value, span);
}

void base::profinet::DcpHelloRequest::UpdateSize()
{
	SetDataLength(_block_stream->Length());

	// 头部长度 10 字节加上 Blocks 的长度。
	_fid_apdu.SetValidPayloadSize(10 + DataLength());
}

#pragma endregion

base::profinet::DcpHelloRequest::DcpHelloRequest(base::Span const &span)
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

base::profinet::DcpServiceIdEnum base::profinet::DcpHelloRequest::ServiceId() const
{
	return static_cast<base::profinet::DcpServiceIdEnum>(_this_span[0]);
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpHelloRequest::ServiceType() const
{
	return static_cast<base::profinet::DcpServiceTypeEnum>(_this_span[1]);
}

uint32_t base::profinet::DcpHelloRequest::Xid() const
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	return _converter.ToUInt32(span);
}

void base::profinet::DcpHelloRequest::SetXid(uint32_t value)
{
	base::Span span = _this_span.Slice(base::Range{2, 6});
	_converter.GetBytes(value, span);
}

uint16_t base::profinet::DcpHelloRequest::DataLength() const
{
	base::Span span = _this_span.Slice(base::Range{8, 10});
	return _converter.ToUInt16(span);
}

#pragma endregion

#pragma region Blocks

void base::profinet::DcpHelloRequest::ClearAllBlocks()
{
	SetDataLength(0);
	_block_stream->Clear();

	// Blocks 区的有效数据长度为 0，只剩下头部的 10 字节是有效数据。
	_fid_apdu.SetValidPayloadSize(10);
}

void base::profinet::DcpHelloRequest::PutNameOfStationBlock(std::string const &station_name)
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

	UpdateSize();
}

void base::profinet::DcpHelloRequest::PutIPAddressInfomationBlock(bool ip_not_set,
																  base::IPAddress const &ip,
																  base::IPAddress const &gateway,
																  base::IPAddress const &netmask)
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

#pragma endregion
