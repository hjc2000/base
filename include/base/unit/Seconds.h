#pragma once
#include <base/math/Fraction.h>
#include <chrono>

namespace base
{
    class Hz;

    /// @brief 周期。单位：秒。
    class Seconds
    {
    private:
        base::Fraction _value{1};

    public:
        Seconds() = default;
        Seconds(Seconds const &o);
        Seconds(base::Fraction const &value);
        Seconds(int64_t value);
        Seconds(base::Hz const &value);
        Seconds(std::chrono::seconds const &value);
        Seconds(std::chrono::milliseconds const &value);
        Seconds(std::chrono::microseconds const &value);

        Seconds &operator=(Seconds const &o);

#pragma region 强制类型转换

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
            return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
        }

        explicit operator std::chrono::microseconds() const
        {
            return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
        }

#pragma endregion

        Seconds operator-() const;
        Seconds operator+(Seconds const &value) const;
        Seconds operator-(Seconds const &value) const;
        Seconds operator*(Seconds const &value) const;
        Seconds operator/(Seconds const &value) const;

        Seconds &operator+=(Seconds const &value);
        Seconds &operator-=(Seconds const &value);
        Seconds &operator*=(Seconds const &value);
        Seconds &operator/=(Seconds const &value);
    };
} // namespace base

std::ostream &operator<<(std::ostream &ostream, base::Seconds const &right);
base::Seconds operator+(int64_t left, base::Seconds const &right);
base::Seconds operator-(int64_t left, base::Seconds const &right);
base::Seconds operator*(int64_t left, base::Seconds const &right);
base::Seconds operator/(int64_t left, base::Seconds const &right);
