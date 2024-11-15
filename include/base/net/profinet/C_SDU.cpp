#include "C_SDU.h"

base::profinet::C_SDU::C_SDU(base::Span const &span)
{
    _span = span;
}

base::Span &base::profinet::C_SDU::Span()
{
    return _span;
}

base::Span const &base::profinet::C_SDU::Span() const
{
    return _span;
}
