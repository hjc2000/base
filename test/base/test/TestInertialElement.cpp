#include "TestInertialElement.h" // IWYU pragma: keep
#include "base/math/FastInt64Fraction.h"
#include "base/math/InertialElement.h"
#include "base/string/define.h"
#include <cstdint>
#include <iostream>

#if HAS_THREAD

void base::test::TestInertialElement()
{
	std::cout << std::endl
			  << CODE_POS_STR;

	base::InertialElement inertial_element{
		base::FastInt64Fraction{1, static_cast<int64_t>(1e9)},
		base::FastInt64Fraction{1, static_cast<int64_t>(1e12)},
	};

	std::cout << "Kx: " << inertial_element.Kx() << std::endl;
	std::cout << "Ky: " << inertial_element.Ky() << std::endl;

	for (int64_t i = 0; i < 1000; i++)
	{
		inertial_element.Input(base::FastInt64Fraction{10000, 100});
		std::cout << inertial_element.CurrentOutput() << std::endl;
		std::cout << base::floor(inertial_element.CurrentOutput()) << std::endl;
		std::cout << std::endl;
	}
}

#endif // HAS_THREAD
