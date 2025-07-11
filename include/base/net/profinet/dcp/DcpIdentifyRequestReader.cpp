#include "DcpIdentifyRequestReader.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include "DcpHeaderReader.h"
#include "DcpTlvReader.h"

base::profinet::DcpIdentifyRequestReader::DcpIdentifyRequestReader(base::ReadOnlySpan const &span)
	: _fid_pdu_reader(span)
{
	_this_span = _fid_pdu_reader.Payload();
	if (_this_span.Size() < base::profinet::DcpHeaderReader::HeaderSize())
	{
		// DCP 头部要 10 字节，这里连 10 字节都没有。
		throw std::invalid_argument{CODE_POS_STR + "传入的帧中不含有合法的 DCP 头部。"};
	}

	_header_reader = std::shared_ptr<base::profinet::DcpHeaderReader>{new base::profinet::DcpHeaderReader{
		_this_span,
	}};

	{
		base::ReadOnlySpan tlv_span = _this_span.Slice(base::Range{
			base::profinet::DcpHeaderReader::HeaderSize(),
			_this_span.Size(),
		});

		_tlv_reader = std::shared_ptr<base::profinet::DcpTlvReader>{new base::profinet::DcpTlvReader{
			tlv_span,
		}};
	}
}

base::profinet::DcpServiceIdEnum base::profinet::DcpIdentifyRequestReader::ServiceId() const
{
	return _header_reader->ServiceId();
}

base::profinet::DcpServiceTypeEnum base::profinet::DcpIdentifyRequestReader::ServiceType() const
{
	return _header_reader->ServiceType();
}

uint32_t base::profinet::DcpIdentifyRequestReader::Xid() const
{
	return _header_reader->Xid();
}

uint16_t base::profinet::DcpIdentifyRequestReader::ResponseDelay() const
{
	return _header_reader->ResponseDelay();
}

uint16_t base::profinet::DcpIdentifyRequestReader::DataLength() const
{
	return _header_reader->DataLength();
}

bool base::profinet::DcpIdentifyRequestReader::HasNameOfStationBlock() const
{
	return _tlv_reader->HasNameOfStationBlock();
}

std::string base::profinet::DcpIdentifyRequestReader::NameOfStation() const
{
	return _tlv_reader->NameOfStation();
}

base::Json base::profinet::DcpIdentifyRequestReader::ToJson() const
{
	base::Json root{
		{"ServiceId", base::to_string(ServiceId())},
		{"ServiceType", base::to_string(ServiceType())},
		{"Xid", base::ToHexString(Xid())},
		{"ResponseDelay", base::ToHexString(ResponseDelay())},
		{"DataLength", DataLength()},
	};

	base::Json blocks;
	if (HasNameOfStationBlock())
	{
		blocks["NameOfStation"] = NameOfStation();
	}

	root["Blocks"] = blocks;
	return root;
}

#if HAS_THREAD

void base::profinet::test::TestDcpIdentifyRequestReader()
{
	uint8_t const buffer[] = {0x1, 0xe, 0xcf, 0x0, 0x0, 0x0, 0xb0, 0x25,
							  0xaa, 0x39, 0xe9, 0x1c, 0x88, 0x92, 0xfe,
							  0xfe, 0x5, 0x0, 0x0, 0x0, 0x1, 0x17, 0x0,
							  0x1, 0x0, 0x10, 0x2, 0x2, 0x0, 0xb, 0x72,
							  0x74, 0x2d, 0x6c, 0x61, 0x62, 0x73, 0x2d,
							  0x64, 0x65, 0x76, 0x0, 0x0, 0x0, 0x0, 0x0,
							  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
							  0x0, 0x0, 0x0, 0x0, 0x0};

	base::profinet::DcpIdentifyRequestReader reader{base::ReadOnlySpan{buffer, sizeof(buffer)}};
	std::cout << reader << std::endl;
}

#endif
