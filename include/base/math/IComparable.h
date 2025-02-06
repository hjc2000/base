#pragma once
#include <base/math/IEqualable.h>
#include <stdexcept>
#include <type_traits>

namespace base
{
	/// @brief 比较结果。
	enum class ComparisonResult
	{
		/// @brief 大于
		Greater,

		/// @brief 等于
		Equal,

		/// @brief 小于
		Less,
	};

	/// @brief 比较接口。
	/// @tparam TAnother
	template <typename TAnother>
	class IComparable :
		public base::IEqualable<TAnother>
	{
	private:
#pragma region sfinae

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
								 std::void_t<decltype(std::declval<IComparable<TAnother>>() < std::declval<t_another>())>> :
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
									std::void_t<decltype(std::declval<IComparable<TAnother>>() > std::declval<t_another>())>> :
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
									   std::void_t<decltype(std::declval<IComparable<TAnother>>() <= std::declval<t_another>())>> :
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
										  std::void_t<decltype(std::declval<IComparable<TAnother>>() >= std::declval<t_another>())>> :
			std::true_type
		{
		};

#pragma endregion

	public:
		/// @brief 本对象大于 another.
		/// @param another
		/// @return
		virtual bool GreaterThan(TAnother const &another) const = 0;

		/// @brief 本对象小于 another.
		/// @param another
		/// @return
		virtual bool LessThan(TAnother const &another) const = 0;

		/// @brief 比较。
		/// @param another
		/// @return
		base::ComparisonResult Compare(TAnother const &another) const
		{
			if (Equal(another))
			{
				return base::ComparisonResult::Equal;
			}

			if (LessThan(another))
			{
				return base::ComparisonResult::Less;
			}

			if (GreaterThan(another))
			{
				return base::ComparisonResult::Greater;
			}

			throw std::runtime_error{"错误的 Compare 实现。不可能既不等于，又不小于，又不大于。"};
		}

#pragma region 比较运算符

		auto operator<(TAnother const &value) const
			-> std::enable_if_t<!has_less_operator<TAnother>::value, bool>
		{
			return LessThan(value);
		}

		auto operator>(TAnother const &value) const
			-> std::enable_if_t<!has_greater_operator<TAnother>::value, bool>
		{
			return GreaterThan(value);
		}

		auto operator<=(TAnother const &value) const
			-> std::enable_if_t<!has_less_equal_operator<TAnother>::value, bool>
		{
			if (LessThan(value))
			{
				return true;
			}

			if (Equal(value))
			{
				return true;
			}

			return false;
		}

		auto operator>=(TAnother const &value) const
			-> std::enable_if_t<!has_greater_equal_operator<TAnother>::value, bool>
		{
			if (GreaterThan(value))
			{
				return true;
			}

			if (Equal(value))
			{
				return true;
			}

			return false;
		}

#pragma endregion
	};
} // namespace base
