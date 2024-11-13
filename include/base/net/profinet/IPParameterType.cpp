#include "IPParameterType.h"

base::profinet::IPParameterType::IPParameterType(base::Span const &span)
{
}

uint8_t base::profinet::IPParameterType::IPOption() const
{
    return 0;
}

uint8_t base::profinet::IPParameterType::SuboptionIPParameter() const
{
    return 0;
}
