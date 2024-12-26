#include "DataObjectElement.h"

base::profinet::DataObjectElement::DataObjectElement(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::DataObjectElement::Span() const
{
	return _span;
}

base::Span base::profinet::DataObjectElement::Data() const
{
	return base::Span();
}

void base::profinet::DataObjectElement::SetData(base::Span const &value)
{
	Data().CopyFrom(value);
}

uint8_t base::profinet::DataObjectElement::Iops() const
{
	return 0;
}

void base::profinet::DataObjectElement::SetIops(uint8_t value)
{
}
