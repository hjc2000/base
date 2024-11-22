#include "IPEndPoint.h"

base::IPEndPoint::IPEndPoint(base::IPAddress const &ip, uint16_t port)
{
    _ip_address = ip;
    _port = port;
}

base::IPEndPoint::IPEndPoint(IPEndPoint const &o)
{
    *this = o;
}

base::IPEndPoint &base::IPEndPoint::operator=(IPEndPoint const &o)
{
    _ip_address = o._ip_address;
    _port = o._port;
    return *this;
}

base::IPAddress base::IPEndPoint::IPAddress() const
{
    return _ip_address;
}

void base::IPEndPoint::SetIPAddress(base::IPAddress const &value)
{
    _ip_address = value;
}

uint16_t base::IPEndPoint::Port() const
{
    return _port;
}

void base::IPEndPoint::SetPort(uint16_t value)
{
    _port = value;
}