#include "DcpTlvReader.h"
#include "base/bit/AutoBitConverter.h"
#include "DcpTlvEnumerable.h"
#include <stdexcept>

base::profinet::DcpTlvReader::DcpTlvReader(base::ReadOnlySpan const &span)
{
	base::profinet::DcpTlvEnumerable tlv_collection{span};
	for (base::ReadOnlySpan tlv : tlv_collection)
	{
		uint8_t option = tlv[0];
		uint8_t suboption = tlv[1];
		if (option == 2 && suboption == 2)
		{
			_has_name_of_station_block = true;
			uint16_t length = base::big_endian_remote_converter.FromBytes<uint16_t>(tlv.Slice(base::Range{2, 4}));
			base::ReadOnlySpan name_span = tlv.Slice(4, length);
			_station_name = std::string{reinterpret_cast<char const *>(name_span.Buffer()), length};
		}
	}
}

bool base::profinet::DcpTlvReader::HasNameOfStationBlock() const
{
	return _has_name_of_station_block;
}

std::string base::profinet::DcpTlvReader::NameOfStation() const
{
	if (!_has_name_of_station_block)
	{
		throw std::runtime_error{CODE_POS_STR + "没有站点名称块。"};
	}

	return _station_name;
}
