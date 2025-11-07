#pragma once
#include "base/math/Fraction.h"
#include "base/sfinae/is_coefficient.h"
#include "base/sfinae/is_unit.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <type_traits>

namespace base
{
	namespace unit
	{
		///
		/// @brief 单位类的接口。
		///
		///
		template <typename TSelf>
		class IUnit :
			public base::ICanToString
		{
		public:
			/* #region 接口 */

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			virtual base::Fraction &Value() = 0;

			///
			/// @brief 单位的字符串。
			///
			/// @return
			///
			virtual std::string UnitString() const = 0;

			/* #endregion */

			/* #region 强制转换运算符 */

			explicit operator base::Fraction() const
			{
				return Value();
			}

			explicit operator uint64_t() const
			{
				return static_cast<uint64_t>(Value());
			}

			explicit operator int64_t() const
			{
				return static_cast<int64_t>(Value());
			}

			explicit operator uint32_t() const
			{
				return static_cast<uint32_t>(Value());
			}

			explicit operator int32_t() const
			{
				return static_cast<int32_t>(Value());
			}

			explicit operator uint16_t() const
			{
				return static_cast<uint16_t>(Value());
			}

			explicit operator int16_t() const
			{
				return static_cast<int16_t>(Value());
			}

			explicit operator uint8_t() const
			{
				return static_cast<uint8_t>(Value());
			}

			explicit operator int8_t() const
			{
				return static_cast<int8_t>(Value());
			}

			explicit operator int() const
				requires(!std::is_same_v<int, int32_t>)
			{
				return static_cast<int8_t>(Value());
			}

			explicit operator double() const
			{
				return static_cast<double>(Value());
			}

			/* #endregion */

			///
			/// @brief 转化为字符串
			///
			/// @return
			///
			virtual std::string ToString() const override
			{
				std::string ret = Value().ToString();
				std::string unit_string = UnitString();
				if (unit_string.size() > 0)
				{
					ret += " " + unit_string;
				}

				return ret;
			}

			///
			/// @brief 单位的值。
			///
			/// @return
			///
			base::Fraction const &Value() const
			{
				return const_cast<IUnit<TSelf> *>(this)->Value();
			}

			/* #region 计算函数 */

			///
			/// @brief 向下取整
			///
			/// @return
			///
			TSelf Floor() const
			{
				return TSelf{Value().Floor()};
			}

			///
			/// @brief 向上取整
			///
			/// @return
			///
			TSelf Ceil() const
			{
				return TSelf{Value().Ceil()};
			}

			/* #endregion */

			/* #region 算术运算 */

			///
			/// @brief 取相反数。
			///
			/// @return
			///
			TSelf operator-() const
			{
				return -Value();
			}

			///
			/// @brief 加上本单位或能够转换为本单位的其他单位的值。
			///
			/// @param value
			///
			/// @return
			///
			TSelf operator+(TSelf const &value) const
			{
				return TSelf{Value() + value.Value()};
			}

			///
			/// @brief 减去本单位或能够转换为本单位的其他单位的值。
			///
			/// @param value
			///
			/// @return
			///
			TSelf operator-(TSelf const &value) const
			{
				return TSelf{Value() - value.Value()};
			}

			///
			/// @brief 乘上无量纲的系数。
			///
			/// @param value
			///
			/// @return
			///
			template <typename _type>
				requires(base::is_coefficient<_type>)
			TSelf operator*(_type const &value) const
			{
				return TSelf{Value() * value};
			}

			///
			/// @brief 除以一个无量纲的系数。
			///
			/// @param value
			///
			/// @return
			///
			template <typename _type>
				requires(base::is_coefficient<_type>)
			TSelf operator/(_type const &value) const
			{
				return TSelf{Value() / value};
			}

			///
			/// @brief 除以本单位，变成一个无量纲的常数。
			///
			/// @param value
			///
			/// @return
			///
			base::Fraction operator/(TSelf const &value) const
			{
				return Value() / value.Value();
			}

			/* #endregion */

			/* #region 自改变算术运算符 */

			///
			/// @brief 加上本单位。
			///
			/// @param value
			///
			/// @return
			///
			TSelf &operator+=(TSelf const &value)
			{
				Value() += value.Value();
				return *reinterpret_cast<TSelf *>(this);
			}

			///
			/// @brief 减去本单位。
			///
			/// @param value
			///
			/// @return
			///
			TSelf &operator-=(TSelf const &value)
			{
				Value() -= value.Value();
				return *reinterpret_cast<TSelf *>(this);
			}

			///
			/// @brief 乘上无量纲的系数。
			///
			/// @param value
			///
			/// @return
			///
			template <typename _type>
				requires(base::is_coefficient<_type>)
			TSelf &operator*=(_type const &value)
			{
				Value() *= value;
				return *reinterpret_cast<TSelf *>(this);
			}

			///
			/// @brief 除以一个无量纲的系数。
			///
			/// @param value
			///
			/// @return
			///
			template <typename _type>
				requires(base::is_coefficient<_type>)
			TSelf &operator/=(_type const &value)
			{
				Value() /= value;
				return *reinterpret_cast<TSelf *>(this);
			}

			/* #endregion */

			/* #region 比较 */

			bool operator<(TSelf const &other) const
			{
				return Value() < other.Value();
			}

			bool operator>(TSelf const &other) const
			{
				return Value() > other.Value();
			}

			bool operator<=(TSelf const &other) const
			{
				return Value() <= other.Value();
			}

			bool operator>=(TSelf const &other) const
			{
				return Value() >= other.Value();
			}

			/* #endregion */
		};

	} // namespace unit

	///
	/// @brief 向下取整
	///
	/// @param value
	///
	/// @return
	///
	template <typename TUnit>
		requires(base::unit::is_unit<TUnit>)
	inline TUnit floor(base::unit::IUnit<TUnit> const &value)
	{
		return value.Floor();
	}

	///
	/// @brief 向上取整
	///
	/// @param value
	///
	/// @return
	///
	template <typename TUnit>
		requires(base::unit::is_unit<TUnit>)
	inline TUnit ceil(base::unit::IUnit<TUnit> const &value)
	{
		return value.Ceil();
	}

} // namespace base

template <typename TLeft, typename TRight>
	requires(base::unit::is_unit<TLeft> &&
			 base::unit::is_unit<TRight> &&
			 std::is_convertible_v<TRight, TLeft>)
inline bool operator==(TLeft const &left, TRight const &right)
{
	return left.Value() == TLeft{right}.Value();
}

///
/// @brief 单位乘上一个无量纲的系数。
///
/// @param left
/// @param right
///
/// @return
///
template <typename TLeft, typename TRight>
	requires(base::is_coefficient<TLeft> && base::unit::is_unit<TRight>)
inline TRight operator*(TLeft const &left, base::unit::IUnit<TRight> const &right)
{
	return reinterpret_cast<TRight const &>(right) * left;
}
