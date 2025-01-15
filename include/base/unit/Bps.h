#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>

namespace base
{
	class Mbps;

	/// @brief 比特率。每秒的比特数。这里是 bit / s.
	class Bps :
		public base::ICanToString
	{
	private:
		base::Fraction _value = 0;

	public:
#pragma region 生命周期
		Bps() = default;
		Bps(int64_t value);
		Bps(base::Fraction const &o);
		Bps(Mbps const &o);
		Bps(Bps const &o);
		base::Bps &operator=(Bps const &o);
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
		base::Bps operator-() const;
		base::Bps operator+(Bps const &value) const;
		base::Bps operator-(Bps const &value) const;
		base::Bps operator*(Bps const &value) const;
		base::Bps operator/(Bps const &value) const;
		base::Bps &operator+=(Bps const &value);
		base::Bps &operator-=(Bps const &value);
		base::Bps &operator*=(Bps const &value);
		base::Bps &operator/=(Bps const &value);

		base::Bps operator+(base::Mbps const &value) const;
		base::Bps operator-(base::Mbps const &value) const;
		base::Bps operator*(base::Mbps const &value) const;
		base::Bps operator/(base::Mbps const &value) const;
		base::Bps &operator+=(base::Mbps const &value);
		base::Bps &operator-=(base::Mbps const &value);
		base::Bps &operator*=(base::Mbps const &value);
		base::Bps &operator/=(base::Mbps const &value);
#pragma endregion

#pragma region 比较运算符
		bool operator==(Bps const &value) const;
		bool operator<(Bps const &value) const;
		bool operator>(Bps const &value) const;
		bool operator<=(Bps const &value) const;
		bool operator>=(Bps const &value) const;

		bool operator==(base::Mbps const &value) const;
		bool operator<(base::Mbps const &value) const;
		bool operator>(base::Mbps const &value) const;
		bool operator<=(base::Mbps const &value) const;
		bool operator>=(base::Mbps const &value) const;
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

namespace std
{
	/// @brief 向下取整
	/// @param value
	/// @return
	int64_t floor(base::Bps const &value);

	/// @brief 向上取整
	/// @param value
	/// @return
	int64_t ceil(base::Bps const &value);
} // namespace std
