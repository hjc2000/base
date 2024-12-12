#pragma once
#include <stdint.h>

namespace base
{
    class Mbps
    {
    private:
        int64_t _value = 0;

    public:
        Mbps() = default;
        Mbps(int64_t value);
        Mbps(Mbps const &o);
        base::Mbps &operator=(Mbps const &o);
    };
} // namespace base
