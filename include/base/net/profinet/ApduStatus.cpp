#include "ApduStatus.h"

base::profinet::ApduStatus::ApduStatus(base::Span const &span)
{
    _span = span;
}

base::Span &base::profinet::ApduStatus::Span()
{
    return _span;
}

base::Span const &base::profinet::ApduStatus::Span() const
{
    return _span;
}
