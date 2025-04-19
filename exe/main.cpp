#include "base/bit/bit.h"
#include "base/container/Dictionary.h"
#include "base/container/Set.h"
#include "base/math/Fraction.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	{
		base::Fraction f{base::Double{std::numbers::pi}};
		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(17)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(17)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(17)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;
	}

	{
		uint32_t reg = 5;
		std::cout << base::bit::ReadBits(reg, 2, 3) << std::endl;
	}

	base::test::test_set();
	base::test::TestDictionary();
}
