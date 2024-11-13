#include "IPParameterBlockRes.h"

base::profinet::IPParameterType base::profinet::IPParameterBlockRes::Type() const
{
    return IPParameterType();
}

uint16_t base::profinet::IPParameterBlockRes::BlockLength() const
{
    return 0;
}

uint16_t base::profinet::IPParameterBlockRes::BlockInfo() const
{
    return 0;
}

base::profinet::IPParameterValue base::profinet::IPParameterBlockRes::Value() const
{
    return IPParameterValue();
}
