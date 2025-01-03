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
		base::Mbps operator-() const;
		base::Mbps operator+(Mbps const &value) const;
		base::Mbps operator-(Mbps const &value) const;
		base::Mbps operator*(Mbps const &value) const;
		base::Mbps operator/(Mbps const &value) const;
		base::Mbps &operator+=(Mbps const &value);
		base::Mbps &operator-=(Mbps const &value);
		base::Mbps &operator*=(Mbps const &value);
		base::Mbps &operator/=(Mbps const &value);

		base::Mbps operator+(base::Bps const &value) const;
		base::Mbps operator-(base::Bps const &value) const;
		base::Mbps operator*(base::Bps const &value) const;
		base::Mbps operator/(base::Bps const &value) const;
		base::Mbps &operator+=(base::Bps const &value);
		base::Mbps &operator-=(base::Bps const &value);
		base::Mbps &operator*=(base::Bps const &value);
		base::Mbps &operator/=(base::Bps const &value);
#pragma endregion

#pragma region 比较运算符
		bool operator==(Mbps const &value) const;
		bool operator<(Mbps const &value) const;
		bool operator>(Mbps const &value) const;
		bool operator<=(Mbps const &value) const;
		bool operator>=(Mbps const &value) const;

		bool operator==(base::Bps const &value) const;
		bool operator<(base::Bps const &value) const;
		bool operator>(base::Bps const &value) const;
		bool operator<=(base::Bps const &value) const;
		bool operator>=(base::Bps const &value) const;
#pragma endregion

		/// @brief 转化为字符串
		/// @return
		std::string ToString() const override;
	};
} // namespace base

std::ostream &operator<<(std::ostream &ostream, base::Mbps const &right);
base::Mbps operator+(int64_t left, base::Mbps const &right);
base::Mbps operator-(int64_t left, base::Mbps const &right);
base::Mbps operator*(int64_t left, base::Mbps const &right);
base::Mbps operator/(int64_t left, base::Mbps const &right);
