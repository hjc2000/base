#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include "base/string/define.h"
#include "base/wrapper/number-wrapper.h"
#include <cstdint>
#include <iostream>

int main()
{
	{
		std::cout << CODE_POS_STR;

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
		std::cout << CODE_POS_STR;

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
		std::cout << CODE_POS_STR;

		float f_pi = static_cast<float>(std::numbers::pi);
		base::Int64Fraction f{base::Float{f_pi}};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "f_pi: \t\t"
				  << std::setprecision(precision)
				  << f_pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 float: \t"
				  << std::setprecision(precision)
				  << static_cast<float>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<float>(f) - f_pi
				  << std::endl;
	}
}
