#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>

namespace base
{
	class BigInteger
	{
	private:
		boost::multiprecision::cpp_int _value;

	public:
		BigInteger() = default;

		BigInteger(int64_t value)
		{
			_value = value;
		}

		BigInteger(boost::multiprecision::cpp_int const &value)
		{
			_value = value;
		}

	public:
		explicit operator int64_t() const
		{
			return static_cast<int64_t>(_value);
		}

	public:
		BigInteger operator+(BigInteger const &right_value) const
		{
			return BigInteger{_value + right_value._value};
		}

		BigInteger operator-(BigInteger const &right_value) const
		{
			return BigInteger{_value - right_value._value};
		}

		BigInteger operator*(BigInteger const &right_value) const
		{
			return BigInteger{_value * right_value._value};
		}

		BigInteger operator/(BigInteger const &right_value) const
		{
			return BigInteger{_value / right_value._value};
		}

		BigInteger &operator+=(BigInteger const &right_value)
		{
			_value += right_value._value;
			return *this;
		}

		BigInteger &operator-=(BigInteger const &right_value)
		{
			_value -= right_value._value;
			return *this;
		}

		BigInteger &operator*=(BigInteger const &right_value)
		{
			_value *= right_value._value;
			return *this;
		}

		BigInteger &operator/=(BigInteger const &right_value)
		{
			_value /= right_value._value;
			return *this;
		}

		BigInteger operator-() const
		{
			return BigInteger{-_value};
		}

		BigInteger &operator++()
		{
			++_value;
			return *this;
		}

		BigInteger operator++(int)
		{
			BigInteger ret{*this};
			_value++;
			return ret;
		}

	public:
		bool operator==(BigInteger const &another)
		{
			return _value == another._value;
		}

		bool operator<(BigInteger const &another)
		{
			return _value < another._value;
		}

		bool operator>(BigInteger const &another)
		{
			return _value > another._value;
		}

		bool operator<=(BigInteger const &another)
		{
			return _value <= another._value;
		}

		bool operator>=(BigInteger const &another)
		{
			return _value >= another._value;
		}
	};
} // namespace base
