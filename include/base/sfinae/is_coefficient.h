#pragma once
#include "base/math/FastInt64Fraction.h"
#include "base/math/Fraction.h"
#include <type_traits>

namespace base
{
	///
	/// @brief 概念，检查一个数是不是系数。
	///
	///
	template <typename T>
	concept is_coefficient = requires(T t) {
		requires(std::is_integral_v<T> ||
				 std::is_floating_point_v<T> ||
				 std::convertible_to<T, base::Fraction> ||
				 std::convertible_to<T, base::FastInt64Fraction>);
	};

} // namespace base
