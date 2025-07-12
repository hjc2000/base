#include "base/math/Fraction.h"
#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include "base/stream/ReadOnlySpan.h"
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
		base::InertialElement<base::Int64Fraction> inertial_element{
			base::Int64Fraction{1, static_cast<int64_t>(1e6)},
			base::Int64Fraction{1, static_cast<int64_t>(1e9)},
			base::Int64Fraction{1, static_cast<int64_t>(1) << 32},
		};

		std::cout << "Kx: " << inertial_element.Kx() << std::endl;
		std::cout << "Ky: " << inertial_element.Ky() << std::endl;

		for (int i = 0; i < 10000; i++)
		{
			inertial_element.Input(100);
		}

		std::cout << base::floor(inertial_element.CurrentOutput()) << std::endl;
	}

	{
		constexpr uint8_t buffer_a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		constexpr uint8_t buffer_b[10] = {2, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		base::ReadOnlySpan span_a{buffer_a, sizeof(buffer_a)};
		base::ReadOnlySpan span_b{buffer_b, sizeof(buffer_b)};
		bool compare_result = span_a < span_b;
		std::cout << compare_result << std::endl;
	}
}
