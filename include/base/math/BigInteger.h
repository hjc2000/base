#pragma once
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep

namespace base
{
	using BigInteger = boost::multiprecision::cpp_int;

	///
	/// @brief 将大整型转换为字符串。
	///
	/// @param value
	/// @return
	///
	std::string to_string(base::BigInteger const &value);

} // namespace base
