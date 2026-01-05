#include "TestFactorExtractor.h" // IWYU pragma: keep
#include "base/math/FactorExtractor.h"
#include "base/string/define.h"
#include <cstdint>
#include <iostream>
#include <stdexcept>

#if HAS_THREAD

void base::test::TestFactorExtractor()
{
	{
		std::cout << "测试无限制大小的贪心地提取因数：" << std::endl;
		constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
		constexpr uint64_t base_num = 7;
		base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

		factor_extractor.ExtractGreedily(2);
		factor_extractor.ExtractGreedily(3);
		factor_extractor.ExtractGreedily(5);

		if (factor_extractor.Factor() * factor_extractor.Base() != factor * base_num)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		std::cout << "系数: " << factor_extractor.Factor() << std::endl;
		std::cout << "基数: " << factor_extractor.Base() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "测试有限制大小的贪心地提取因数：" << std::endl;
		constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
		constexpr uint64_t base_num = 7;
		base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

		factor_extractor.ExtractGreedily(2, 8);
		factor_extractor.ExtractGreedily(3, 8);
		factor_extractor.ExtractGreedily(5, 8);

		if (factor_extractor.Factor() * factor_extractor.Base() != factor * base_num)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		std::cout << "系数: " << factor_extractor.Factor() << std::endl;
		std::cout << "基数: " << factor_extractor.Base() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "测试有限制大小的保守地提取因数：" << std::endl;
		constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
		constexpr uint64_t base_num = 7;
		base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

		factor_extractor.ExtractConservatively(2, 63);
		factor_extractor.ExtractConservatively(3, 63);
		factor_extractor.ExtractConservatively(5, 63);

		if (factor_extractor.Factor() * factor_extractor.Base() != factor * base_num)
		{
			throw std::runtime_error{CODE_POS_STR + "测试不通过。"};
		}

		std::cout << "系数: " << factor_extractor.Factor() << std::endl;
		std::cout << "基数: " << factor_extractor.Base() << std::endl;
		std::cout << std::endl;
	}
}

#endif // HAS_THREAD
