#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class SecondPeriod;

    class Hz
    {
    private:
        base::Fraction _value{1};

    public:
        Hz() = default;
        Hz(Hz const &o);
        Hz(base::Fraction const &value);
        Hz(int64_t value);
        Hz(base::SecondPeriod const &value);

        Hz &operator=(Hz const &o);

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
