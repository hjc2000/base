#pragma once
#include <type_traits>

namespace base
{
	/// @brief 可进行相等比较的接口。
	/// @tparam TAnother
	template <typename TAnother>
	class IEqualable
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
								  std::void_t<decltype(std::declval<IEqualable<TAnother>>() == std::declval<t_another>())>> :
			std::true_type
		{
		};

#pragma endregion

	public:
		/// @brief 本对象等于 another.
		/// @param another
		/// @return
		virtual bool Equal(TAnother const &another) = 0;

		/// @brief 如果没有已经定义的相等运算符，就重载相等运算符。
		/// @param value
		/// @return
		auto operator==(TAnother const &value) const
			-> std::enable_if_t<!has_equal_operator<TAnother>::value, bool>
		{
			return Equal(value);
		}
	};
} // namespace base
