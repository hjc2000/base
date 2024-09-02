#pragma once
#include <base/math/Fraction.h>
#include <chrono>

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

        explicit operator std::chrono::seconds() const
        {
            return std::chrono::seconds{static_cast<int64_t>(_value)};
        }

        explicit operator std::chrono::milliseconds() const
        {
            return std::chrono::milliseconds{static_cast<std::chrono::seconds>(*this)};
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

std::ostream &operator<<(std::ostream &ostream, base::SecondPeriod const &right);
base::SecondPeriod operator+(int64_t left, base::SecondPeriod const &right);
base::SecondPeriod operator-(int64_t left, base::SecondPeriod const &right);
base::SecondPeriod operator*(int64_t left, base::SecondPeriod const &right);
base::SecondPeriod operator/(int64_t left, base::SecondPeriod const &right);
