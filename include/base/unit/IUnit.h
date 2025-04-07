#pragma once
#include "base/math/Fraction.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <type_traits>

namespace base
{
	///
	/// @brief 单位类的接口。
	///
	///
	template <typename TSelf>
	class IUnit :
		public base::ICanToString
	{
	private:
		/* #region 判断是否有比较运算符的模板 */

		///
		/// @brief 有等于运算符
		///
		///
		template <typename t_another, typename = void>
		struct has_equal_operator :
			std::false_type
		{
		};

		///
		/// @brief 有等于运算符
		///
		///
		template <typename t_another>
		struct has_equal_operator<t_another,
								  std::void_t<decltype(std::declval<TSelf>() == std::declval<t_another>())>> :
			std::true_type
		{
		};

		///
		/// @brief 有小于运算符
		///
		///
		template <typename t_another, typename = void>
		struct has_less_operator :
			std::false_type
		{
		};

		///
		/// @brief 有小于运算符
		///
		///
		template <typename t_another>
		struct has_less_operator<t_another,
								 std::void_t<decltype(std::declval<TSelf>() < std::declval<t_another>())>> :
			std::true_type
		{
		};

		///
		/// @brief 有大于运算符
		///
		///
		template <typename t_another, typename = void>
		struct has_greater_operator :
			std::false_type
		{
		};

		///
		/// @brief 有大于运算符
		///
		///
		template <typename t_another>
		struct has_greater_operator<t_another,
									std::void_t<decltype(std::declval<TSelf>() > std::declval<t_another>())>> :
			std::true_type
		{
		};

		///
		/// @brief 有小于等于运算符
		///
		///
		template <typename t_another, typename = void>
		struct has_less_equal_operator :
			std::false_type
		{
		};

		///
		/// @brief 有小于等于运算符
		///
		///
		template <typename t_another>
		struct has_less_equal_operator<t_another,
									   std::void_t<decltype(std::declval<TSelf>() <= std::declval<t_another>())>> :
			std::true_type
		{
		};

		///
		/// @brief 有大于等于运算符
		///
		///
		template <typename t_another, typename = void>
		struct has_greater_equal_operator :
			std::false_type
		{
		};

		///
		/// @brief 有大于等于运算符
		///
		///
		template <typename t_another>
		struct has_greater_equal_operator<t_another,
										  std::void_t<decltype(std::declval<TSelf>() >= std::declval<t_another>())>> :
			std::true_type
		{
		};

		///
		/// @brief 是否使能比较运算符的判定模板
		///
		/// @note 必须得是显式构造的单位类型对象才能与本对象比较，此时才允许使能比较运算符。
		///
		template <typename _type>
		using enable_compare_judge = std::enable_if_t<!std::convertible_to<_type, int64_t> &&
														  !std::convertible_to<_type, base::Fraction> &&
														  !has_equal_operator<_type>::value,
													  bool>;

		/* #endregion */

	public:
		/* #region 接口 */

		///
		/// @brief 单位的值。
		///
		/// @return base::Fraction&
		///
		virtual base::Fraction &Value() = 0;

		///
		/// @brief 单位的字符串。
		///
		/// @return std::string
		///
		virtual std::string UnitString() const = 0;

		/* #endregion */

		/* #region 强制转换运算符 */

		explicit operator base::Fraction() const
		{
			return Value();
		}

		explicit operator int64_t() const
		{
			return static_cast<int64_t>(Value());
		}

		explicit operator double() const
		{
			return static_cast<double>(Value());
		}

		/* #endregion */

		///
		/// @brief 转化为字符串
		///
		/// @return std::string
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
		/// @return base::Fraction const&
		///
		base::Fraction const &Value() const
		{
			return const_cast<IUnit<TSelf> *>(this)->Value();
		}

		/* #region 计算函数 */

		///
		/// @brief 向下取整
		///
		/// @return TSelf
		///
		TSelf Floor() const
		{
			return TSelf{Value().Floor()};
		}

		///
		/// @brief 向上取整
		///
		/// @return TSelf
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
		/// @return TSelf
		///
		TSelf operator-() const
		{
			return -Value();
		}

		///
		/// @brief 加上本单位或能够转换为本单位的其他单位的值。
		///
		/// @param value
		/// @return TSelf
		///
		template <typename _type>
		auto operator+(_type const &value) const
			-> std::enable_if_t<!std::convertible_to<_type, int64_t> &&
									!std::convertible_to<_type, base::Fraction>,
								TSelf>
		{
			return TSelf{Value() + TSelf{value}.Value()};
		}

		///
		/// @brief 减去本单位或能够转换为本单位的其他单位的值。
		///
		/// @param value
		/// @return TSelf
		///
		template <typename _type>
		auto operator-(_type const &value) const
			-> std::enable_if_t<!std::convertible_to<_type, int64_t> &&
									!std::convertible_to<_type, base::Fraction>,
								TSelf>
		{
			return TSelf{Value() - TSelf{value}.Value()};
		}

		///
		/// @brief 乘上无量纲的系数。
		///
		/// @param value
		/// @return TSelf
		///
		template <typename _type>
		auto operator*(_type const &value) const
			-> std::enable_if_t<std::convertible_to<_type, int64_t> ||
									std::convertible_to<_type, base::Fraction>,
								TSelf>
		{
			return TSelf{Value() * value};
		}

		///
		/// @brief 除以一个无量纲的系数。
		///
		/// @param value
		/// @return TSelf
		///
		template <typename _type>
		auto operator/(_type const &value) const
			-> std::enable_if_t<std::convertible_to<_type, int64_t> ||
									std::convertible_to<_type, base::Fraction>,
								TSelf>
		{
			return TSelf{Value() / value};
		}

		///
		/// @brief 除以本单位或能够转换为本单位的其他单位，变成一个无量纲的常数。
		///
		/// @param value
		/// @return base::Fraction
		///
		template <typename _type>
		auto operator/(_type const &value) const
			-> std::enable_if_t<!std::convertible_to<_type, int64_t> &&
									!std::convertible_to<_type, base::Fraction>,
								base::Fraction>
		{
			return Value() / TSelf{value}.Value();
		}

		/* #endregion */

		/* #region 自改变算术运算符 */

		///
		/// @brief 加上本单位或能够转换为本单位的其他单位的值。
		///
		/// @param value
		/// @return TSelf &
		///
		template <typename _type>
		auto operator+=(_type const &value)
			-> std::enable_if_t<!std::convertible_to<_type, int64_t> &&
									!std::convertible_to<_type, base::Fraction>,
								TSelf &>
		{
			Value() += TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		///
		/// @brief 减去本单位或能够转换为本单位的其他单位的值。
		///
		/// @param value
		/// @return TSelf &
		///
		template <typename _type>
		auto operator-=(_type const &value)
			-> std::enable_if_t<!std::convertible_to<_type, int64_t> &&
									!std::convertible_to<_type, base::Fraction>,
								TSelf &>
		{
			Value() -= TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		///
		/// @brief 乘上无量纲的系数。
		///
		/// @param value
		/// @return sTSelf &
		///
		template <typename _type>
		auto operator*=(_type const &value)
			-> std::enable_if_t<std::convertible_to<_type, int64_t> ||
									std::convertible_to<_type, base::Fraction>,
								TSelf &>
		{
			Value() *= value;
			return *reinterpret_cast<TSelf *>(this);
		}

		///
		/// @brief 除以一个无量纲的系数。
		///
		/// @param value
		/// @return TSelf &
		///
		template <typename _type>
		auto operator/=(_type const &value)
			-> std::enable_if_t<std::convertible_to<_type, int64_t> ||
									std::convertible_to<_type, base::Fraction>,
								TSelf &>
		{
			Value() /= value;
			return *reinterpret_cast<TSelf *>(this);
		}

		/* #endregion */

		/* #region 比较 */

		template <typename T>
		auto operator==(T const &value) const -> enable_compare_judge<T>
		{
			return Value() == TSelf{value}.Value();
		}

		template <typename T>
		auto operator<(T const &value) const -> enable_compare_judge<T>
		{
			return Value() < TSelf{value}.Value();
		}

		template <typename T>
		auto operator>(T const &value) const -> enable_compare_judge<T>
		{
			return Value() > TSelf{value}.Value();
		}

		template <typename T>
		auto operator<=(T const &value) const -> enable_compare_judge<T>
		{
			return Value() <= TSelf{value}.Value();
		}

		template <typename T>
		auto operator>=(T const &value) const -> enable_compare_judge<T>
		{
			return Value() >= TSelf{value}.Value();
		}

		/* #endregion */
	};
} // namespace base

///
/// @brief 单位乘上一个无量纲的系数。
///
/// @param left
/// @param right
///
/// @return TUnit
///
template <typename TLeft, typename TUnit>
inline auto operator*(TLeft const &left, base::IUnit<TUnit> const &right)
	-> std::enable_if_t<std::convertible_to<TLeft, int64_t> ||
							std::convertible_to<TLeft, base::Fraction>,
						TUnit>
{
	return right * left;
}

namespace std
{
	///
	/// @brief 向下取整
	///
	/// @param value
	/// @return TUnit
	///
	template <typename TUnit>
	inline TUnit floor(base::IUnit<TUnit> const &value)
	{
		return value.Floor();
	}

	///
	/// @brief 向上取整
	///
	/// @param value
	/// @return TUnit
	///
	template <typename TUnit>
	inline TUnit ceil(base::IUnit<TUnit> const &value)
	{
		return value.Ceil();
	}
} // namespace std
