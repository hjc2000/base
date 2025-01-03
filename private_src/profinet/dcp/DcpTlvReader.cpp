#include "DcpTlvReader.h"

base::profinet::DcpTlvReader::DcpTlvReader(base::ReadOnlySpan const &span)
{
	_span = span;
}

bool base::profinet::DcpTlvReader::HasNameOfStationBlock() const
{
	return false;
}

std::string base::profinet::DcpTlvReader::NameOfStation() const
{
	if (!HasNameOfStationBlock())
	{
		throw std::runtime_error{CODE_POS_STR + "HasNameOfStationBlock 为 false."};
	}

	return std::string();
}
