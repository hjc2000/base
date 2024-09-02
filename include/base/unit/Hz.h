#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class Hz
    {
    private:
        base::Fraction _value{1};

    public:
        Hz(base::Fraction value)
        {
            _value = value;
        }

        base::Fraction Value() const
        {
            return _value;
        }

        operator base::Fraction() const
        {
            return _value;
        }
    };
} // namespace base
