#pragma once
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <type_traits>

namespace base
{
	class BigInteger final :
		public base::ICanToString
	{
	private:
		boost::multiprecision::cpp_int _value;

	public:
		/* #region 构造函数 */

		BigInteger() = default;

		template <typename T, typename std::enable_if<std::is_integral_v<T>, int>::type = 0>
		BigInteger(T value)
		{
			_value = value;
		}

		BigInteger(boost::multiprecision::cpp_int const &cpp_int_value)
		{
			_value = cpp_int_value;
		}

		BigInteger(base::String const &value)
		{
			_value = boost::multiprecision::cpp_int{value.StdString()};
		}

		/* #endregion */

		/* #region 强制转换运算符 */

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

		explicit operator double() const
		{
			return static_cast<double>(_value);
		}

		explicit operator float() const
		{
			return static_cast<float>(_value);
		}

		explicit operator bool() const
		{
			return static_cast<bool>(_value);
		}

		explicit operator boost::multiprecision::cpp_int() const
		{
			return _value;
		}

		/* #endregion */

		/* #region 自增、自减 */

		///
		/// @brief 前缀递增。
		///
		/// @return BigInteger&
		///
		BigInteger &operator++()
		{
			++_value;
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		/// @return BigInteger
		///
		BigInteger operator++(int)
		{
			BigInteger ret{*this};
			++_value;
			return ret;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return BigInteger&
		///
		BigInteger &operator--()
		{
			--_value;
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return BigInteger
		///
		BigInteger operator--(int)
		{
			BigInteger ret{*this};
			--_value;
			return ret;
		}

		/* #endregion */

		/* #region 算术运算 */

		///
		/// @brief 取相反数。
		///
		/// @return BigInteger
		///
		BigInteger operator-() const
		{
			return BigInteger{-_value};
		}

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

		/* #endregion */

		/* #region 自改变算术运算 */

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

		/* #endregion */

		/* #region 比较 */

		bool operator==(BigInteger const &another) const
		{
			return _value == another._value;
		}

		bool operator<(BigInteger const &another) const
		{
			return _value < another._value;
		}

		bool operator>(BigInteger const &another) const
		{
			return _value > another._value;
		}

		bool operator<=(BigInteger const &another) const
		{
			return _value <= another._value;
		}

		bool operator>=(BigInteger const &another) const
		{
			return _value >= another._value;
		}

		/* #endregion */

		///
		/// @brief 转化为字符串
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		boost::multiprecision::cpp_int &Value()
		{
			return _value;
		}

		boost::multiprecision::cpp_int const &Value() const
		{
			return _value;
		}
	};

#if HAS_THREAD
	namespace test
	{
		void TestBigInteger();
	} // namespace test
#endif
} // namespace base
