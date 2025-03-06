#pragma once
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <string>

namespace base
{
	class BigInteger :
		public base::ICanToString
	{
	private:
		boost::multiprecision::cpp_int _value;

	public:
		BigInteger() = default;

		BigInteger(int64_t value)
		{
			_value = value;
		}

		BigInteger(uint64_t value)
		{
			_value = value;
		}

		BigInteger(int32_t value)
		{
			_value = value;
		}

		BigInteger(uint32_t value)
		{
			_value = value;
		}

		BigInteger(int16_t value)
		{
			_value = value;
		}

		BigInteger(uint16_t value)
		{
			_value = value;
		}

		BigInteger(int8_t value)
		{
			_value = value;
		}

		BigInteger(uint8_t value)
		{
			_value = value;
		}

		BigInteger(boost::multiprecision::cpp_int const &value)
		{
			_value = value;
		}

		BigInteger(base::String const &value)
		{
			_value = boost::multiprecision::cpp_int{value.StdString()};
		}

		virtual ~BigInteger() = default;

	public:
		explicit operator int64_t() const
		{
			return static_cast<int64_t>(_value);
		}

		explicit operator uint64_t() const
		{
			return static_cast<uint64_t>(_value);
		}

		explicit operator int32_t() const
		{
			return static_cast<int32_t>(_value);
		}

		explicit operator uint32_t() const
		{
			return static_cast<uint32_t>(_value);
		}

		explicit operator int16_t() const
		{
			return static_cast<int16_t>(_value);
		}

		explicit operator uint16_t() const
		{
			return static_cast<uint16_t>(_value);
		}

		explicit operator int8_t() const
		{
			return static_cast<int8_t>(_value);
		}

		explicit operator uint8_t() const
		{
			return static_cast<uint8_t>(_value);
		}

		explicit operator bool() const
		{
			return static_cast<bool>(_value);
		}

		explicit operator boost::multiprecision::cpp_int() const
		{
			return _value;
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

	public:
		/**
		 * @brief 转化为字符串
		 *
		 * @return std::string
		 */
		virtual std::string ToString() const override;
	};

#if HAS_THREAD
	namespace test
	{
		void TestBigInteger();
	} // namespace test
#endif
} // namespace base
