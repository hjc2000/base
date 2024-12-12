#pragma once
#include <stdint.h>

namespace base
{
    class Bps
    {
    private:
        int64_t _value = 0;

    public:
        Bps() = default;
        Bps(int64_t value);
        Bps(Bps const &o);
        base::Bps &operator=(Bps const &o);
    };
} // namespace base
