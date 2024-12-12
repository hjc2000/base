#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
    /// @brief 比特率。每秒的比特数。这里是 bit / s.
    class Bps :
        public base::ICanToString
    {
    private:
        base::Fraction _value = 0;

    public:
        Bps() = default;
        Bps(int64_t value);
        Bps(base::Fraction const &o);
        Bps(Bps const &o);
        base::Bps &operator=(Bps const &o);

        base::Fraction &Value()
        {
            return _value;
        }

        base::Fraction const &Value() const
        {
            return _value;
        }

#pragma region 强制转换运算符

        explicit operator base::Fraction() const
        {
            return _value;
        }

        explicit operator int64_t() const
        {
            return static_cast<int64_t>(_value);
        }

        explicit operator double() const
        {
            return static_cast<double>(_value);
        }

        explicit operator std::string() const
        {
            return static_cast<std::string>(_value);
        }

#pragma endregion

#pragma region 四则运算符

        Bps operator-() const
        {
            return -_value;
        }

        Bps operator+(Bps const &value) const
        {
            return _value + static_cast<base::Fraction>(value);
        }

        Bps operator-(Bps const &value) const
        {
            return _value - static_cast<base::Fraction>(value);
        }

        Bps operator*(Bps const &value) const
        {
            return _value * static_cast<base::Fraction>(value);
        }

        Bps operator/(Bps const &value) const
        {
            return _value / static_cast<base::Fraction>(value);
        }

        Bps &operator+=(Bps const &value)
        {
            _value += static_cast<base::Fraction>(value);
            return *this;
        }

        Bps &operator-=(Bps const &value)
        {
            _value -= static_cast<base::Fraction>(value);
            return *this;
        }

        Bps &operator*=(Bps const &value)
        {
            _value *= static_cast<base::Fraction>(value);
            return *this;
        }

        Bps &operator/=(Bps const &value)
        {
            _value /= static_cast<base::Fraction>(value);
            return *this;
        }

#pragma endregion

#pragma region 比较运算符

        bool operator==(Bps const &value) const
        {
            return _value == value._value;
        }

        bool operator<(Bps const &value) const
        {
            return _value < value._value;
        }

        bool operator>(Bps const &value) const
        {
            return _value > value._value;
        }

        bool operator<=(Bps const &value) const
        {
            return _value <= value._value;
        }

        bool operator>=(Bps const &value) const
        {
            return _value >= value._value;
        }

#pragma endregion

        /// @brief 转化为字符串
        /// @return
        std::string ToString() const override
        {
            return _value.ToString();
        }
    };
} // namespace base

std::ostream &operator<<(std::ostream &ostream, base::Bps const &right);
base::Bps operator+(int64_t left, base::Bps const &right);
base::Bps operator-(int64_t left, base::Bps const &right);
base::Bps operator*(int64_t left, base::Bps const &right);
base::Bps operator/(int64_t left, base::Bps const &right);
