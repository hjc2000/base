#include "C_SDU.h"

base::profinet::C_SDU::C_SDU(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::C_SDU::Span() const
{
	return _span;
}

base::profinet::DataItem base::profinet::C_SDU::DataItem() const
{
	return base::profinet::DataItem();
}

void base::profinet::C_SDU::SetDataItem(base::profinet::DataItem const &value)
{
	DataItem().Span().CopyFrom(value.Span());
}

base::Span base::profinet::C_SDU::Padding() const
{
	return base::Span();
}
