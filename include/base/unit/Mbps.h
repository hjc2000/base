#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
	class Bps;

	/// @brief 比特率。每秒的比特数。这里是 Mbit / s.
	/// @note 在通信领域，1 Mbit = 1000 * 1000 bit.
	class Mbps :
		public base::ICanToString
	{
	private:
		base::Fraction _value = 0;

	public:
#pragma region 生命周期
		Mbps() = default;
		Mbps(int64_t value);
		Mbps(base::Fraction const &o);
		Mbps(Mbps const &o);
		Mbps(base::Bps const &o);
		base::Mbps &operator=(Mbps const &o);
#pragma endregion

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

		base::Mbps operator-() const
		{
			return -_value;
		}

		base::Mbps operator+(Mbps const &value) const
		{
			return _value + static_cast<base::Fraction>(value);
		}

		base::Mbps operator-(Mbps const &value) const
		{
			return _value - static_cast<base::Fraction>(value);
		}

		base::Mbps operator*(Mbps const &value) const
		{
			return _value * static_cast<base::Fraction>(value);
		}

		base::Mbps operator/(Mbps const &value) const
		{
			return _value / static_cast<base::Fraction>(value);
		}

		base::Mbps &operator+=(Mbps const &value)
		{
			_value += static_cast<base::Fraction>(value);
			return *this;
		}

		base::Mbps &operator-=(Mbps const &value)
		{
			_value -= static_cast<base::Fraction>(value);
			return *this;
		}

		base::Mbps &operator*=(Mbps const &value)
		{
			_value *= static_cast<base::Fraction>(value);
			return *this;
		}

		base::Mbps &operator/=(Mbps const &value)
		{
			_value /= static_cast<base::Fraction>(value);
			return *this;
		}

		base::Mbps operator+(base::Bps const &value) const
		{
			return *this + base::Mbps{value};
		}

		base::Mbps operator-(base::Bps const &value) const
		{
			return *this - base::Mbps{value};
		}

		base::Mbps operator*(base::Bps const &value) const
		{
			return *this * base::Mbps{value};
		}

		base::Mbps operator/(base::Bps const &value) const
		{
			return *this / base::Mbps{value};
		}

		base::Mbps &operator+=(base::Bps const &value)
		{
			*this += base::Mbps{value};
			return *this;
		}

		base::Mbps &operator-=(base::Bps const &value)
		{
			*this -= base::Mbps{value};
			return *this;
		}

		base::Mbps &operator*=(base::Bps const &value)
		{
			*this *= base::Mbps{value};
			return *this;
		}

		base::Mbps &operator/=(base::Bps const &value)
		{
			*this /= base::Mbps{value};
			return *this;
		}

#pragma endregion

#pragma region 比较运算符

		bool operator==(Mbps const &value) const
		{
			return _value == value._value;
		}

		bool operator<(Mbps const &value) const
		{
			return _value < value._value;
		}

		bool operator>(Mbps const &value) const
		{
			return _value > value._value;
		}

		bool operator<=(Mbps const &value) const
		{
			return _value <= value._value;
		}

		bool operator>=(Mbps const &value) const
		{
			return _value >= value._value;
		}

		bool operator==(base::Bps const &value) const
		{
			return *this == base::Mbps{value};
		}

		bool operator<(base::Bps const &value) const
		{
			return *this < base::Mbps{value};
		}

		bool operator>(base::Bps const &value) const
		{
			return *this > base::Mbps{value};
		}

		bool operator<=(base::Bps const &value) const
		{
			return *this <= base::Mbps{value};
		}

		bool operator>=(base::Bps const &value) const
		{
			return *this >= base::Mbps{value};
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

std::ostream &operator<<(std::ostream &ostream, base::Mbps const &right);
base::Mbps operator+(int64_t left, base::Mbps const &right);
base::Mbps operator-(int64_t left, base::Mbps const &right);
base::Mbps operator*(int64_t left, base::Mbps const &right);
base::Mbps operator/(int64_t left, base::Mbps const &right);

namespace std
{
	/// @brief 向下取整
	/// @param value
	/// @return
	int64_t floor(base::Mbps const &value);

	/// @brief 向上取整
	/// @param value
	/// @return
	int64_t ceil(base::Mbps const &value);
} // namespace std
