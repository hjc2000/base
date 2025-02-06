#pragma once
#include <type_traits>

namespace base
{
	template <typename TAnother>
	class IEqualable
	{
	private:
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

	public:
		/// @brief 本对象等于 another.
		/// @param another
		/// @return
		virtual bool Equal(TAnother const &another) = 0;

		auto operator==(TAnother const &value) const
			-> std::enable_if_t<!has_equal_operator<TAnother>::value, bool>
		{
			return Equal(value);
		}
	};
} // namespace base
