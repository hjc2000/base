#include "base/math/Fraction.h"
#include "base/math/InertialElement.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
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
		base::InertialElement<base::Fraction> inertial_element{
			base::Fraction{1, static_cast<int64_t>(1e6)},
			base::Fraction{1, static_cast<int64_t>(1e9)},
			base::Fraction{1, static_cast<int64_t>(1e20)},
		};

		std::cout << "Kx: " << inertial_element.Kx() << std::endl;
		std::cout << "Ky: " << inertial_element.Ky() << std::endl;

		for (int i = 0; i < 1000; i++)
		{
			std::cout << inertial_element.Input(100) << std::endl;
		}

		std::cout << base::floor(inertial_element.CurrentOutput()) << std::endl;
	}
}
