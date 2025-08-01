#include "base/math/Fraction.Test.h"
#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include "base/string/define.h"
#include <cstdint>
#include <iostream>

int main()
{
	{
		std::cout << std::endl
				  << CODE_POS_STR;

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

	base::test::TestFraction();
	base::test::TestInt64Fraction();
}
