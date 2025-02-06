#pragma once
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
	class IComparable
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
								  std::void_t<decltype(std::declval<IComparable<TAnother>>() == std::declval<t_another>())>> :
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
		/// @brief 比较。
		/// @param another
		/// @return
		virtual base::ComparisonResult Compare(TAnother const &another) = 0;

#pragma region 比较运算符

		auto operator==(TAnother const &value) const
			-> std::enable_if_t<!has_equal_operator<TAnother>::value, bool>
		{
			return Compare(value) == base::ComparisonResult::Equal;
		}

		auto operator<(TAnother const &value) const
			-> std::enable_if_t<!has_less_operator<TAnother>::value, bool>
		{
			return Compare(value) == base::ComparisonResult::Less;
		}

		auto operator>(TAnother const &value) const
			-> std::enable_if_t<!has_greater_operator<TAnother>::value, bool>
		{
			return Compare(value) == base::ComparisonResult::Greater;
		}

		auto operator<=(TAnother const &value) const
			-> std::enable_if_t<!has_less_equal_operator<TAnother>::value, bool>
		{
			if (Compare(value) == base::ComparisonResult::Less)
			{
				return true;
			}

			if (Compare(value) == base::ComparisonResult::Equal)
			{
				return true;
			}

			return false;
		}

		auto operator>=(TAnother const &value) const
			-> std::enable_if_t<!has_greater_equal_operator<TAnother>::value, bool>
		{
			if (Compare(value) == base::ComparisonResult::Greater)
			{
				return true;
			}

			if (Compare(value) == base::ComparisonResult::Equal)
			{
				return true;
			}

			return false;
		}

#pragma endregion
	};
} // namespace base
