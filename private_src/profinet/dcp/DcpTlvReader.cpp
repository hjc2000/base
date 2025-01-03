#include "DcpTlvReader.h"

base::profinet::DcpTlvReader::DcpTlvReader(base::ReadOnlySpan const &span)
	: _tlv_collection(span)
{
	for (base::ReadOnlySpan tlv : _tlv_collection)
	{
		uint8_t option = tlv[0];
		uint8_t suboption = tlv[1];
		if (option == 2 && suboption == 2)
		{
			_name_of_station_block = tlv;
		}
	}
}

bool base::profinet::DcpTlvReader::HasNameOfStationBlock() const
{
	return _name_of_station_block.Size() > 0;
}

std::string base::profinet::DcpTlvReader::NameOfStation() const
{
	if (!HasNameOfStationBlock())
	{
		throw std::runtime_error{CODE_POS_STR + "没有站点名称块。"};
	}

	uint16_t length = _converter.ToUInt16(_name_of_station_block.Slice(base::Range{2, 4}));
	base::ReadOnlySpan name_span = _name_of_station_block.Slice(4, length);
	return std::string{reinterpret_cast<char const *>(name_span.Buffer()), length};
}
