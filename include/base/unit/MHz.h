#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
	class Seconds;
	class Hz;

	/// @brief 频率单位：MHz.
	class MHz :
		public base::ICanToString
	{
	private:
		base::Fraction _value{0};

	public:
#pragma region 生命周期
		/// @brief 0Hz
		MHz() = default;

		/// @brief 拷贝构造函数。
		/// @param o
		MHz(MHz const &o);

		/// @brief 从分数构造频率。
		/// @param value
		MHz(base::Fraction const &value);

		MHz(base::Hz const &value);

		/// @brief 构造整数频率。
		/// @param value
		MHz(int64_t value);

		/// @brief 从秒构造频率。Hz 是 s 的倒数。
		/// @param value
		MHz(base::Seconds const &value);

		/// @brief 赋值运算符。
		/// @param o
		/// @return
		MHz &operator=(MHz const &o);
#pragma endregion

#pragma region 强制转换

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

		/// @brief 向下取整
		/// @return
		int64_t Floor() const
		{
			return _value.Floor();
		}

		/// @brief 向上取整
		/// @return
		int64_t Ceil() const
		{
			return _value.Ceil();
		}

#pragma region 四则运算符

		MHz operator-() const
		{
			return -_value;
		}

		MHz operator+(MHz const &value) const
		{
			return _value + static_cast<base::Fraction>(value);
		}

		MHz operator-(MHz const &value) const
		{
			return _value - static_cast<base::Fraction>(value);
		}

		MHz operator*(MHz const &value) const
		{
			return _value * static_cast<base::Fraction>(value);
		}

		MHz operator/(MHz const &value) const
		{
			return _value / static_cast<base::Fraction>(value);
		}

		MHz &operator+=(MHz const &value)
		{
			_value += static_cast<base::Fraction>(value);
			return *this;
		}

		MHz &operator-=(MHz const &value)
		{
			_value -= static_cast<base::Fraction>(value);
			return *this;
		}

		MHz &operator*=(MHz const &value)
		{
			_value *= static_cast<base::Fraction>(value);
			return *this;
		}

		MHz &operator/=(MHz const &value)
		{
			_value /= static_cast<base::Fraction>(value);
			return *this;
		}

#pragma endregion

#pragma region 比较运算符

		bool operator==(MHz const &value) const
		{
			return _value == value._value;
		}

		bool operator<(MHz const &value) const
		{
			return _value < value._value;
		}

		bool operator>(MHz const &value) const
		{
			return _value > value._value;
		}

		bool operator<=(MHz const &value) const
		{
			return _value <= value._value;
		}

		bool operator>=(MHz const &value) const
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
