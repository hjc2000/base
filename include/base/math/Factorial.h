#pragma once
#include <base/math/BigInteger.h>
#include <base/string/define.h>

namespace base
{
	/**
	 * @brief 阶乘。
	 *
	 * @param num
	 * @return base::BigInteger
	 */
	base::BigInteger Factorial(base::BigInteger num);
} // namespace base
