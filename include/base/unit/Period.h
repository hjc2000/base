#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class Hz;

    class Period
    {
    private:
        base::Fraction _value;

    public:
        Period(base::Fraction const &value);
        Period(int64_t value);
        Period(base::Hz const &value);

        base::Fraction Value() const
        {
            return _value;
        }
    };
} // namespace base
