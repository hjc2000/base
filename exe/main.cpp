#include "base/bit/bit.h"
#include "base/Counter.h"
#include "base/math/Fraction.h"
#include "base/string/Parse.h"
#include "base/string/ToHexString.h"
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

	base::test::test_parse_double();

	{
		constexpr uint64_t a = static_cast<uint64_t>(0x123) << 52;
		constexpr uint64_t b = base::bit::ReadBits(a, 52, 63);
		std::cout << base::ToHexString(a) << std::endl;
		std::cout << base::ToHexString(b) << std::endl;
	}

	{
		base::Counter<uint8_t> counter{254};
		for (int i = 0; i < 256; i++)
		{
			std::cout << std::to_string(counter.CurrentValue()) << std::endl;
			// counter++;
			counter--;
		}
	}
}
