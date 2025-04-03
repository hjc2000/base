#pragma once
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep

namespace base
{
	///
	/// @brief 阶乘。
	///
	/// @param num
	/// @return boost::multiprecision::cpp_int
	///
	boost::multiprecision::cpp_int Factorial(boost::multiprecision::cpp_int num);
} // namespace base
