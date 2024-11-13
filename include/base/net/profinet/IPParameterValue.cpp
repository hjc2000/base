#include "IPParameterValue.h"

base::IPAddress base::profinet::IPParameterValue::IP() const
{
    return IPAddress();
}

base::IPAddress base::profinet::IPParameterValue::Subnetmask() const
{
    return IPAddress();
}

base::IPAddress base::profinet::IPParameterValue::StandardGateway() const
{
    return IPAddress();
}
