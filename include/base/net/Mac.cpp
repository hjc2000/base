#include "Mac.h"

base::Mac::Mac(base::Array<uint8_t, 6> const &mac_buffer)
{
    _mac_buffer = mac_buffer;
}

base::Mac::Mac(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
}

base::Mac &base::Mac::operator=(Mac const &o)
{
    _mac_buffer = o._mac_buffer;
    return *this;
}

base::Mac::operator base::Array<uint8_t, 6>() const
{
    return _mac_buffer;
}
