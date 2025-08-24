#include "TestFactorExtractor.h" // IWYU pragma: keep
#include "base/math/FactorExtractor.h"
#include <cstdint>
#include <iostream>

#if HAS_THREAD

void base::test::TestFactorExtractor()
{
	{
		std::cout << "测试无限制大小的提取因数：" << std::endl;
		constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
		constexpr uint64_t base_num = 7;
		base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

		factor_extractor.Extract(3);
		factor_extractor.Extract(4);
		factor_extractor.Extract(5);
		std::cout << "系数: " << factor_extractor.Factor() << std::endl;
		std::cout << "基数: " << factor_extractor.Base() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "测试有限制大小的提取因数：" << std::endl;
		constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
		constexpr uint64_t base_num = 7;
		base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

		factor_extractor.Extract(3, 9);
		factor_extractor.Extract(4, 9);
		factor_extractor.Extract(5, 9);
		std::cout << "系数: " << factor_extractor.Factor() << std::endl;
		std::cout << "基数: " << factor_extractor.Base() << std::endl;
		std::cout << std::endl;
	}
}

#endif // HAS_THREAD
