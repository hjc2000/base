#pragma once
#include "base/math/Fraction.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <ostream>
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
		/* #region 类型 */

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

		template <typename _type>
		using enable_compare_condition = std::enable_if_t<!std::is_same_v<_type, int64_t> &&
															  !std::is_same_v<_type, base::Fraction> &&
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

		base::Fraction const &Value() const
		{
			return const_cast<IUnit<TSelf> *>(this)->Value();
		}

		///
		/// @brief 向下取整
		///
		/// @return int64_t
		///
		int64_t Floor() const
		{
			return Value().Floor();
		}

		///
		/// @brief 向上取整
		///
		/// @return int64_t
		///
		int64_t Ceil() const
		{
			return Value().Ceil();
		}

		/* #region 算术运算 */

		TSelf operator-() const
		{
			return -Value();
		}

		template <typename T>
		TSelf operator+(T const &value) const
		{
			return TSelf{Value() + TSelf{value}.Value()};
		}

		template <typename T>
		TSelf operator-(T const &value) const
		{
			return TSelf{Value() - TSelf{value}.Value()};
		}

		template <typename T>
		TSelf operator*(T const &value) const
		{
			return TSelf{Value() * TSelf{value}.Value()};
		}

		template <typename T>
		TSelf operator/(T const &value) const
		{
			return TSelf{Value() / TSelf{value}.Value()};
		}

		template <typename T>
		TSelf &operator+=(T const &value)
		{
			Value() += TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		template <typename T>
		TSelf &operator-=(T const &value)
		{
			Value() -= TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		template <typename T>
		TSelf &operator*=(T const &value)
		{
			Value() *= TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		template <typename T>
		TSelf &operator/=(T const &value)
		{
			Value() /= TSelf{value}.Value();
			return *reinterpret_cast<TSelf *>(this);
		}

		/* #endregion */

		/* #region 比较 */

		template <typename T>
		auto operator==(T const &value) const -> enable_compare_condition<T>
		{
			return Value() == TSelf{value}.Value();
		}

		template <typename T>
		auto operator<(T const &value) const -> enable_compare_condition<T>
		{
			return Value() < TSelf{value}.Value();
		}

		template <typename T>
		auto operator>(T const &value) const -> enable_compare_condition<T>
		{
			return Value() > TSelf{value}.Value();
		}

		template <typename T>
		auto operator<=(T const &value) const -> enable_compare_condition<T>
		{
			return Value() <= TSelf{value}.Value();
		}

		template <typename T>
		auto operator>=(T const &value) const -> enable_compare_condition<T>
		{
			return Value() >= TSelf{value}.Value();
		}

		/* #endregion */
	};
} // namespace base

///
/// @brief 将 IUnit 输出到输出流。
///
/// @param ostream
/// @param right
/// @return template <typename T>&
///
template <typename T>
inline std::ostream &operator<<(std::ostream &ostream, base::IUnit<T> const &right)
{
	ostream << right.ToString();
	return ostream;
}

///
/// @brief IUnit 乘法。
///
/// @param left
/// @param right
/// @return template <typename T>
///
template <typename T>
inline T operator*(base::Fraction const &left, base::IUnit<T> const &right)
{
	return T{left * static_cast<base::Fraction>(right)};
}

namespace std
{
	///
	/// @brief 向下取整
	///
	/// @param value
	/// @return template <typename T>
	///
	template <typename T>
	inline int64_t floor(base::IUnit<T> const &value)
	{
		return value.Floor();
	}

	///
	/// @brief 向上取整
	///
	/// @param value
	/// @return template <typename T>
	///
	template <typename T>
	inline int64_t ceil(base::IUnit<T> const &value)
	{
		return value.Ceil();
	}
} // namespace std
