#include "TestCounter.h" // IWYU pragma: keep
#include "base/math/Counter.h"
#include <cstdint>
#include <iostream>

void base::test::TestCounter()
{
	{
		std::cout << std::endl
				  << "测试递增: " << std::endl;

		base::Counter<uint64_t> counter{0, 9};
		for (int i = 0; i < 20; i++)
		{
			std::cout << counter.CurrentValue() << ", ";
			if ((i + 1) % 10 == 0)
			{
				std::cout << std::endl;
			}

			counter++;
		}

		std::cout << std::endl;
	}
}
