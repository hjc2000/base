#pragma once
#include <base/math/Fraction.h>
#include <base/string/ICanToString.h>
#include <ostream>

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
		/// @tparam TAnother
		/// @tparam
		template <typename TAnother, typename = void>
		struct has_equal_operator :
			std::false_type
		{
		};

		/// @brief 有等于运算符
		/// @tparam TAnother
		template <typename TAnother>
		struct has_equal_operator<TAnother,
								  std::void_t<decltype(std::declval<TSelf>() == std::declval<TAnother>())>> :
			std::true_type
		{
		};

		/// @brief 有小于运算符
		/// @tparam TAnother
		/// @tparam
		template <typename TAnother, typename = void>
		struct has_less_operator :
			std::false_type
		{
		};

		/// @brief 有小于运算符
		/// @tparam TAnother
		template <typename TAnother>
		struct has_less_operator<TAnother,
								 std::void_t<decltype(std::declval<TSelf>() < std::declval<TAnother>())>> :
			std::true_type
		{
		};

		/// @brief 有大于运算符
		/// @tparam TAnother
		/// @tparam
		template <typename TAnother, typename = void>
		struct has_greater_operator :
			std::false_type
		{
		};

		/// @brief 有大于运算符
		/// @tparam TAnother
		template <typename TAnother>
		struct has_greater_operator<TAnother,
									std::void_t<decltype(std::declval<TSelf>() > std::declval<TAnother>())>> :
			std::true_type
		{
		};

		/// @brief 有小于等于运算符
		/// @tparam TAnother
		/// @tparam
		template <typename TAnother, typename = void>
		struct has_less_equal_operator :
			std::false_type
		{
		};

		/// @brief 有小于等于运算符
		/// @tparam TAnother
		template <typename TAnother>
		struct has_less_equal_operator<TAnother,
									   std::void_t<decltype(std::declval<TSelf>() <= std::declval<TAnother>())>> :
			std::true_type
		{
		};

		/// @brief 有大于等于运算符
		/// @tparam TAnother
		/// @tparam
		template <typename TAnother, typename = void>
		struct has_greater_equal_operator :
			std::false_type
		{
		};

		/// @brief 有大于等于运算符
		/// @tparam TAnother
		template <typename TAnother>
		struct has_greater_equal_operator<TAnother,
										  std::void_t<decltype(std::declval<TSelf>() >= std::declval<TAnother>())>> :
			std::true_type
		{
		};

#pragma endregion

	public:
		virtual base::Fraction &Value() = 0;

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
		std::string ToString() const override
		{
			return Value().ToString();
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
	ostream << static_cast<base::Fraction>(right);
	return ostream;
}

/// @brief IUnit 四则运算。
/// @tparam T
/// @param left
/// @param right
/// @return
template <typename T>
inline T operator+(int64_t left, base::IUnit<T> const &right)
{
	return T{left + static_cast<base::Fraction>(right)};
}

/// @brief IUnit 四则运算。
/// @tparam T
/// @param left
/// @param right
/// @return
template <typename T>
inline T operator-(int64_t left, base::IUnit<T> const &right)
{
	return T{left - static_cast<base::Fraction>(right)};
}

/// @brief IUnit 四则运算。
/// @tparam T
/// @param left
/// @param right
/// @return
template <typename T>
inline T operator*(int64_t left, base::IUnit<T> const &right)
{
	return T{left * static_cast<base::Fraction>(right)};
}

/// @brief IUnit 四则运算。
/// @tparam T
/// @param left
/// @param right
/// @return
template <typename T>
inline T operator/(int64_t left, base::IUnit<T> const &right)
{
	return T{left / static_cast<base::Fraction>(right)};
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
