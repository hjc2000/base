#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class Seconds;

    class Hz
    {
    private:
        base::Fraction _value{1};

    public:
        Hz() = default;
        Hz(Hz const &o);
        Hz(base::Fraction const &value);
        Hz(int64_t value);
        Hz(base::Seconds const &value);

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

std::ostream &operator<<(std::ostream &ostream, base::Hz const &right);
base::Hz operator+(int64_t left, base::Hz const &right);
base::Hz operator-(int64_t left, base::Hz const &right);
base::Hz operator*(int64_t left, base::Hz const &right);
base::Hz operator/(int64_t left, base::Hz const &right);
