#include "DataItem.h"

base::profinet::DataItem::DataItem(base::Span const &span)
{
	_span = span;
}

base::Span const &base::profinet::DataItem::Span() const
{
	return _span;
}

uint8_t base::profinet::DataItem::Iocs() const
{
	return 0;
}

void base::profinet::DataItem::SetIocs(uint8_t value)
{
}

base::profinet::DataObjectElement base::profinet::DataItem::DataObjectElement() const
{
	return base::profinet::DataObjectElement();
}

void base::profinet::DataItem::SetDataObjectElement(base::profinet::DataObjectElement const &value)
{
	DataObjectElement().Span().CopyFrom(value.Span());
}
