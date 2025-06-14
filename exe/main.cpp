#include "base/math/Fraction.h"
#include "base/math/pow.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	{
		base::Fraction f{base::Double{std::numbers::pi}};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(precision)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(precision)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;
	}

	{
		int64_t result = base::pow<int64_t>(2, 10);
		std::cout << result << std::endl;
	}
	{
		uint64_t result = base::pow<uint64_t>(2, 10);
		std::cout << result << std::endl;
	}
}
