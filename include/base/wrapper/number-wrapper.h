#pragma once
#include <cstdint>
#include <type_traits>

namespace base
{
	///
	/// @brief 通用数值包装器模板
	///
	template <typename T>
	class NumericWrapper
	{
	private:
		T _value{};

	public:
		NumericWrapper() = default;

		constexpr explicit NumericWrapper(T value)
			: _value(value)
		{
		}

		constexpr T Value() const
		{
			return _value;
		}

		constexpr void SetValue(T value)
		{
			_value = value;
		}

		/* #region 算术运算符 */

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

		// 位运算符（仅适用于整数类型）
		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator&(NumericWrapper const &other) const
		{
			return NumericWrapper{_value & other._value};
		}

		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator|(NumericWrapper const &other) const
		{
			return NumericWrapper{_value | other._value};
		}

		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator^(NumericWrapper const &other) const
		{
			return NumericWrapper{_value ^ other._value};
		}

		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator~() const
		{
			return NumericWrapper{~_value};
		}

		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator<<(int shift) const
		{
			return NumericWrapper{_value << shift};
		}

		template <typename U = T, typename = std::enable_if_t<std::is_integral_v<U>>>
		constexpr NumericWrapper operator>>(int shift) const
		{
			return NumericWrapper{_value >> shift};
		}

		/* #region 自增、自减运算符 */

		constexpr NumericWrapper &operator++()
		{
			++_value;
			return *this;
		}

		constexpr NumericWrapper operator++(int)
		{
			NumericWrapper temp{*this};
			++_value;
			return temp;
		}

		constexpr NumericWrapper &operator--()
		{
			--_value;
			return *this;
		}

		constexpr NumericWrapper operator--(int)
		{
			NumericWrapper temp{*this};
			--_value;
			return temp;
		}

		/* #endregion */
	};

	// 使用模板别名定义具体类型的包装器
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
