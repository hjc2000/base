#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
	class Seconds;
	class MHz;

	/// @brief 频率单位：Hz.
	class Hz :
		public base::ICanToString
	{
	private:
		base::Fraction _value{0};

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

		Hz(base::MHz const &value);

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

		Hz operator-() const
		{
			return -_value;
		}

#pragma region 四则运算符

		template <typename T>
		Hz operator+(T const &value) const
		{
			return _value + base::Hz{value}._value;
		}

		template <typename T>
		Hz operator-(T const &value) const
		{
			return _value - base::Hz{value}._value;
		}

		template <typename T>
		Hz operator*(T const &value) const
		{
			return _value * base::Hz{value}._value;
		}

		template <typename T>
		Hz operator/(T const &value) const
		{
			return _value / base::Hz{value}._value;
		}

		template <typename T>
		Hz &operator+=(T const &value)
		{
			_value += base::Hz{value}._value;
			return *this;
		}

		template <typename T>
		Hz &operator-=(T const &value)
		{
			_value -= base::Hz{value}._value;
			return *this;
		}

		template <typename T>
		Hz &operator*=(T const &value)
		{
			_value *= base::Hz{value}._value;
			return *this;
		}

		template <typename T>
		Hz &operator/=(T const &value)
		{
			_value /= base::Hz{value}._value;
			return *this;
		}

#pragma endregion

#pragma region 比较运算符

		template <typename T>
		bool operator==(T const &value) const
		{
			return _value == base::Hz{value}._value;
		}

		template <typename T>
		bool operator<(T const &value) const
		{
			return _value < base::Hz{value}._value;
		}

		template <typename T>
		bool operator>(T const &value) const
		{
			return _value > base::Hz{value}._value;
		}

		template <typename T>
		bool operator<=(T const &value) const
		{
			return _value <= base::Hz{value}._value;
		}

		template <typename T>
		bool operator>=(T const &value) const
		{
			return _value >= base::Hz{value}._value;
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

namespace std
{
	/// @brief 向下取整
	/// @param value
	/// @return
	int64_t floor(base::Hz const &value);

	/// @brief 向上取整
	/// @param value
	/// @return
	int64_t ceil(base::Hz const &value);
} // namespace std
