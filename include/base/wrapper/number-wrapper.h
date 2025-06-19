#pragma once
#include <cstdint>
#include <type_traits>

namespace base
{
	///
	/// @brief 通用数值包装器模板
	///
	template <typename NumberType>
	class NumericWrapper
	{
	private:
		NumberType _value{};

	public:
		/* #region 构造函数 */

		NumericWrapper() = default;

		constexpr explicit NumericWrapper(NumberType value)
			: _value(value)
		{
		}

		/* #endregion */

		constexpr NumberType Value() const
		{
			return _value;
		}

		constexpr void SetValue(NumberType value)
		{
			_value = value;
		}

		/* #region 算术运算符 */

		///
		/// @brief 取相反数。
		///
		/// @return constexpr NumericWrapper
		///
		constexpr NumericWrapper operator-() const
		{
			return NumericWrapper{-_value};
		}

		constexpr NumericWrapper operator+(NumericWrapper const &other) const
		{
			return NumericWrapper{_value + other._value};
		}

		constexpr NumericWrapper operator-(NumericWrapper const &other) const
		{
			return NumericWrapper{_value - other._value};
		}

		constexpr NumericWrapper operator*(NumericWrapper const &other) const
		{
			return NumericWrapper{_value * other._value};
		}

		constexpr NumericWrapper operator/(NumericWrapper const &other) const
		{
			return NumericWrapper{_value / other._value};
		}

		constexpr NumericWrapper operator%(NumericWrapper const &other) const
		{
			return NumericWrapper{_value % other._value};
		}

		/* #endregion */

		/* #region 自改变算术运算符 */

		constexpr NumericWrapper &operator+=(NumericWrapper const &other)
		{
			_value += other._value;
			return *this;
		}

		constexpr NumericWrapper &operator-=(NumericWrapper const &other)
		{
			_value -= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator*=(NumericWrapper const &other)
		{
			_value *= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator/=(NumericWrapper const &other)
		{
			_value /= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator%=(NumericWrapper const &other)
		{
			_value %= other._value;
			return *this;
		}

		/* #endregion */

		/* #region 自增、自减运算符 */

		///
		/// @brief 前缀递增。
		///
		/// @return constexpr NumericWrapper&
		///
		constexpr NumericWrapper &operator++()
		{
			++_value;
			return *this;
		}

		///
		/// @brief 后缀递增。
		///
		/// @return constexpr NumericWrapper
		///
		constexpr NumericWrapper operator++(int)
		{
			NumericWrapper temp{*this};
			++_value;
			return temp;
		}

		///
		/// @brief 前缀递减。
		///
		/// @return constexpr NumericWrapper&
		///
		constexpr NumericWrapper &operator--()
		{
			--_value;
			return *this;
		}

		///
		/// @brief 后缀递减。
		///
		/// @return constexpr NumericWrapper
		///
		constexpr NumericWrapper operator--(int)
		{
			NumericWrapper temp{*this};
			--_value;
			return temp;
		}

		/* #endregion */

		/* #region 位运算符 */

		///
		/// @brief 按位取反。
		///
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator~() const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{~_value};
		}

		///
		/// @brief 按位与。
		///
		/// @param other
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator&(NumericWrapper const &other) const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{_value & other._value};
		}

		///
		/// @brief 按位或。
		///
		/// @param other
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator|(NumericWrapper const &other) const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{_value | other._value};
		}

		///
		/// @brief 按位异或。
		///
		/// @param other
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator^(NumericWrapper const &other) const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{_value ^ other._value};
		}

		///
		/// @brief 左移。
		///
		/// @param shift
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator<<(int shift) const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{_value << shift};
		}

		///
		/// @brief 右移。
		///
		/// @param shift
		/// @return NumericWrapper
		///
		constexpr NumericWrapper operator>>(int shift) const
			requires(std::is_integral_v<NumberType>)
		{
			return NumericWrapper{_value >> shift};
		}

		/* #endregion */

		/* #region 自改变位运算符 */

		constexpr NumericWrapper &operator&=(NumericWrapper const &other)
			requires(std::is_integral_v<NumberType>)
		{
			_value &= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator|=(NumericWrapper const &other)
			requires(std::is_integral_v<NumberType>)
		{
			_value |= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator^=(NumericWrapper const &other)
			requires(std::is_integral_v<NumberType>)
		{
			_value ^= other._value;
			return *this;
		}

		constexpr NumericWrapper &operator<<=(int shift)
			requires(std::is_integral_v<NumberType>)
		{
			_value <<= shift;
			return *this;
		}

		constexpr NumericWrapper &operator>>=(int shift)
			requires(std::is_integral_v<NumberType>)
		{
			_value <<= shift;
			return *this;
		}

		/* #endregion */

		/* #region 比较运算符 */

		constexpr bool operator==(NumericWrapper const &other) const
		{
			return _value == other._value;
		}

		constexpr bool operator!=(NumericWrapper const &other) const
		{
			return _value != other._value;
		}

		constexpr bool operator<(NumericWrapper const &other) const
		{
			return _value < other._value;
		}

		constexpr bool operator>(NumericWrapper const &other) const
		{
			return _value > other._value;
		}

		constexpr bool operator<=(NumericWrapper const &other) const
		{
			return _value <= other._value;
		}

		constexpr bool operator>=(NumericWrapper const &other) const
		{
			return _value >= other._value;
		}

		/* #endregion */
	};

	using Int8 = NumericWrapper<int8_t>;
	using Int16 = NumericWrapper<int16_t>;
	using Int32 = NumericWrapper<int32_t>;
	using Int64 = NumericWrapper<int64_t>;

	using UInt8 = NumericWrapper<uint8_t>;
	using UInt16 = NumericWrapper<uint16_t>;
	using UInt32 = NumericWrapper<uint32_t>;
	using UInt64 = NumericWrapper<uint64_t>;

	using Float = NumericWrapper<float>;
	using Double = NumericWrapper<double>;

} // namespace base
