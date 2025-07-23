#include "base/math/InertialElement.h"
#include "base/math/Int64Fraction.h"
#include "base/stream/memcmp.h"
#include "base/stream/ReadOnlySpan.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

int main()
{
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
		constexpr int32_t result = base::memcmp(buffer_a, buffer_b, 10);
		std::cout << compare_result << std::endl;
		std::cout << result << std::endl;
	}
}
