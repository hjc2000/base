#include "NameOfStationBlockRes.h"

base::profinet::NameOfStationBlockRes::NameOfStationBlockRes(base::Span const &span)
{
}

base::Span &base::profinet::NameOfStationBlockRes::Span()
{
    return _span;
}

base::Span const &base::profinet::NameOfStationBlockRes::Span() const
{
    return _span;
}

base::profinet::NameOfStationType base::profinet::NameOfStationBlockRes::NameOfStationType() const
{
    return base::profinet::NameOfStationType();
}

uint16_t base::profinet::NameOfStationBlockRes::BlockLength() const
{
    return 0;
}

uint16_t base::profinet::NameOfStationBlockRes::BlockInfo() const
{
    return 0;
}

base::Span base::profinet::NameOfStationBlockRes::Name() const
{
    return base::Span();
}
