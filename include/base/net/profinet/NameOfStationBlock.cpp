#include "NameOfStationBlock.h"

base::profinet::NameOfStationBlock::NameOfStationBlock(base::Span const &span)
{
}

base::profinet::NameOfStationType base::profinet::NameOfStationBlock::Type() const
{
	return base::profinet::NameOfStationType();
}

uint16_t base::profinet::NameOfStationBlock::BlockLength() const
{
	return 0;
}

base::Span base::profinet::NameOfStationBlock::Name() const
{
	return base::Span();
}

void base::profinet::NameOfStationBlock::SetName(base::Span const &value)
{
	Name().CopyFrom(value);
}
