#pragma once
#include "base/math/Fraction.h"
#include "base/math/Int64Fraction.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 概念，检查一个数是不是系数。
	///
	///
	template <typename T>
	concept is_coefficient = requires(T t) {
		requires(std::convertible_to<T, int64_t> ||
				 std::convertible_to<T, base::Fraction> ||
				 std::convertible_to<T, base::Int64Fraction>);
	};

} // namespace base
