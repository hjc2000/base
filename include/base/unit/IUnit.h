#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>
#include <ostream>
#include <type_traits>

namespace base
{
	/// @brief 单位类的接口。
	/// @tparam TSelf
	template <typename TSelf>
	class IUnit :
		public base::ICanToString
	{
	private:
#pragma region sfinae

		/// @brief 有等于运算符
		/// @tparam t_another
		/// @tparam
		template <typename t_another, typename = void>
		struct has_equal_operator :
			std::false_type
		{
		};

		/// @brief 有等于运算符
		/// @tparam t_another
		template <typename t_another>
		struct has_equal_operator<t_another,
								  std::void_t<decltype(std::declval<TSelf>() == std::declval<t_another>())>> :
			std::true_type
		{
		};

		/// @brief 有小于运算符
		/// @tparam t_another
		/// @tparam
		template <typename t_another, typename = void>
		struct has_less_operator :
			std::false_type
		{
		};

		/// @brief 有小于运算符
		/// @tparam t_another
		template <typename t_another>
		struct has_less_operator<t_another,
								 std::void_t<decltype(std::declval<TSelf>() < std::declval<t_another>())>> :
			std::true_type
		{
		};

		/// @brief 有大于运算符
		/// @tparam t_another
		/// @tparam
		template <typename t_another, typename = void>
		struct has_greater_operator :
			std::false_type
		{
		};

		/// @brief 有大于运算符
		/// @tparam t_another
		template <typename t_another>
		struct has_greater_operator<t_another,
									std::void_t<decltype(std::declval<TSelf>() > std::declval<t_another>())>> :
			std::true_type
		{
		};

		/// @brief 有小于等于运算符
		/// @tparam t_another
		/// @tparam
		template <typename t_another, typename = void>
		struct has_less_equal_operator :
			std::false_type
		{
		};

		/// @brief 有小于等于运算符
		/// @tparam t_another
		template <typename t_another>
		struct has_less_equal_operator<t_another,
									   std::void_t<decltype(std::declval<TSelf>() <= std::declval<t_another>())>> :
			std::true_type
		{
		};

		/// @brief 有大于等于运算符
		/// @tparam t_another
		/// @tparam
		template <typename t_another, typename = void>
		struct has_greater_equal_operator :
			std::false_type
		{
		};

		/// @brief 有大于等于运算符
		/// @tparam t_another
		template <typename t_another>
		struct has_greater_equal_operator<t_another,
										  std::void_t<decltype(std::declval<TSelf>() >= std::declval<t_another>())>> :
			std::true_type
		{
		};

#pragma endregion

	public:
		virtual base::Fraction &Value() = 0;

		/// @brief 单位的字符串。
		/// @return
		virtual std::string UnitString() const = 0;

		base::Fraction const &Value() const
		{
			return const_cast<IUnit<TSelf> *>(this)->Value();
		}

#pragma region 强制转换

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

#pragma endregion

		/// @brief 向下取整
		/// @return
		int64_t Floor() const
		{
			return Value().Floor();
		}

		/// @brief 向上取整
		/// @return
		int64_t Ceil() const
		{
			return Value().Ceil();
		}

		TSelf operator-() const
		{
			return -Value();
		}

#pragma region 四则运算符

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

#pragma endregion

#pragma region 比较运算符

		template <typename T>
		auto operator==(T const &value) const
			-> std::enable_if_t<!has_equal_operator<T>::value, bool>
		{
			return Value() == TSelf{value}.Value();
		}

		template <typename T>
		auto operator<(T const &value) const
			-> std::enable_if_t<!has_less_operator<T>::value, bool>
		{
			return Value() < TSelf{value}.Value();
		}

		template <typename T>
		auto operator>(T const &value) const
			-> std::enable_if_t<!has_greater_operator<T>::value, bool>
		{
			return Value() > TSelf{value}.Value();
		}

		template <typename T>
		auto operator<=(T const &value) const
			-> std::enable_if_t<!has_less_equal_operator<T>::value, bool>
		{
			return Value() <= TSelf{value}.Value();
		}

		template <typename T>
		auto operator>=(T const &value) const
			-> std::enable_if_t<!has_greater_equal_operator<T>::value, bool>
		{
			return Value() >= TSelf{value}.Value();
		}

#pragma endregion

		/// @brief 转化为字符串
		/// @return
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
	};
} // namespace base

/// @brief 将 IUnit 输出到输出流。
/// @tparam T
/// @param ostream
/// @param right
/// @return
template <typename T>
inline std::ostream &operator<<(std::ostream &ostream, base::IUnit<T> const &right)
{
	ostream << right.ToString();
	return ostream;
}

/// @brief IUnit 乘法。
/// @tparam T
/// @param left
/// @param right
/// @return
template <typename T>
inline T operator*(base::Fraction const &left, base::IUnit<T> const &right)
{
	return T{left * static_cast<base::Fraction>(right)};
}

namespace std
{
	/// @brief 向下取整
	/// @param value
	/// @return
	template <typename T>
	inline int64_t floor(base::IUnit<T> const &value)
	{
		return value.Floor();
	}

	/// @brief 向上取整
	/// @param value
	/// @return
	template <typename T>
	inline int64_t ceil(base::IUnit<T> const &value)
	{
		return value.Ceil();
	}
} // namespace std
