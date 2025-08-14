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
			counter++;
		}

		std::cout << std::endl;
	}

	{
		std::cout << std::endl
				  << "测试递减: " << std::endl;

		base::Counter<uint64_t> counter{0, 9};
		for (int i = 0; i < 20; i++)
		{
			std::cout << counter.CurrentValue() << ", ";
			counter--;
		}

		std::cout << std::endl;
	}

	{
		std::cout << std::endl
				  << "测试随机加减: " << std::endl;

		base::Counter<uint64_t> counter{0, 9};
		counter += 107;
		std::cout << counter.CurrentValue() << std::endl;
		counter -= 106;
		std::cout << counter.CurrentValue() << std::endl;
		std::cout << std::endl;
	}
}
