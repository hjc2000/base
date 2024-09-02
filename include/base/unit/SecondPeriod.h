#pragma once
#include <base/math/Fraction.h>

namespace base
{
    class Hz;

    /// @brief 周期。单位：秒。
    class SecondPeriod
    {
    private:
        base::Fraction _value{1};

    public:
        SecondPeriod() = default;
        SecondPeriod(SecondPeriod const &o);
        SecondPeriod(base::Fraction const &value);
        SecondPeriod(int64_t value);
        SecondPeriod(base::Hz const &value);

        SecondPeriod &operator=(SecondPeriod const &o);

        explicit operator base::Fraction() const
        {
            return _value;
        }

        SecondPeriod operator-() const;
        SecondPeriod operator+(SecondPeriod const &value) const;
        SecondPeriod operator-(SecondPeriod const &value) const;
        SecondPeriod operator*(SecondPeriod const &value) const;
        SecondPeriod operator/(SecondPeriod const &value) const;

        SecondPeriod &operator+=(SecondPeriod const &value);
        SecondPeriod &operator-=(SecondPeriod const &value);
        SecondPeriod &operator*=(SecondPeriod const &value);
        SecondPeriod &operator/=(SecondPeriod const &value);
    };
} // namespace base
