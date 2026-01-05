#pragma once
#include <type_traits>

namespace base
{
	///
	/// @brief 概念。确保 Base 不是 Derived，且是 Derived 的父类。
	///
	///
	template <typename Base, typename Derived>
	concept is_real_base_of = requires() {
		requires(!std::is_same_v<Base, Derived> &&
				 std::is_base_of_v<Base, Derived>);
	};

} // namespace base
