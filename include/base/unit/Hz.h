#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
    class Seconds;

    /// @brief 频率单位：Hz.
    class Hz :
        public base::ICanToString
    {
    private:
        base::Fraction _value{1};

    public:
#pragma region 生命周期
        /// @brief 0Hz
        Hz() = default;

        /// @brief 拷贝构造函数。
        /// @param o
        Hz(Hz const &o);

        /// @brief 从分数构造频率。
        /// @param value
        Hz(base::Fraction const &value);

        /// @brief 构造整数频率。
        /// @param value
        Hz(int64_t value);

        /// @brief 从秒构造频率。Hz 是 s 的倒数。
        /// @param value
        Hz(base::Seconds const &value);

        /// @brief 赋值运算符。
        /// @param o
        /// @return
        Hz &operator=(Hz const &o);
#pragma endregion

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

#pragma region 比较运算符

        bool operator==(Hz const &value) const
        {
            return _value == value._value;
        }

        bool operator<(Hz const &value) const
        {
            return _value < value._value;
        }

        bool operator>(Hz const &value) const
        {
            return _value > value._value;
        }

        bool operator<=(Hz const &value) const
        {
            return _value <= value._value;
        }

        bool operator>=(Hz const &value) const
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

std::ostream &operator<<(std::ostream &ostream, base::Hz const &right);
base::Hz operator+(int64_t left, base::Hz const &right);
base::Hz operator-(int64_t left, base::Hz const &right);
base::Hz operator*(int64_t left, base::Hz const &right);
base::Hz operator/(int64_t left, base::Hz const &right);
