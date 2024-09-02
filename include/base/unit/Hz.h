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

        explicit operator base::Fraction() const
        {
            return _value;
        }

        Hz operator-() const;
        Hz operator+(Hz const &value) const;
        Hz operator-(Hz const &value) const;
        Hz operator*(Hz const &value) const;
        Hz operator/(Hz const &value) const;

        Hz &operator+=(Hz const &value);
        Hz &operator-=(Hz const &value);
        Hz &operator*=(Hz const &value);
        Hz &operator/=(Hz const &value);
    };
} // namespace base
