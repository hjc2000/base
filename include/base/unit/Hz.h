#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class Period;

    class Hz
    {
    private:
        base::Fraction _value{1};

    public:
        Hz(base::Fraction const &value);
        Hz(int64_t value);
        Hz(base::Period const &value);

        base::Fraction Value() const
        {
            return _value;
        }
    };
} // namespace base
