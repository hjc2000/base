#include "TestFactorExtractor.h" // IWYU pragma: keep
#include "base/math/FactorExtractor.h"
#include <cstdint>
#include <iostream>

#if HAS_THREAD

void base::test::TestFactorExtractor()
{
	constexpr uint64_t factor = 3 * 3 * 4 * 4 * 5 * 5;
	constexpr uint64_t base_num = 7;
	base::FactorExtractor<uint64_t> factor_extractor{factor * base_num};

	factor_extractor.Extract(3, 9);
	factor_extractor.Extract(4, 9);
	factor_extractor.Extract(5, 9);
	std::cout << "系数: " << factor_extractor.Factor() << std::endl;
	std::cout << "基数: " << factor_extractor.Base() << std::endl;
}

#endif // HAS_THREAD
