#include "Random.h"
#include <base/define.h>
#include <random>
#include <stdexcept>

#if HAS_THREAD

int64_t base::random::GenerateInt64Random(int64_t min, int64_t max)
{
	// 创建随机数引擎（64 位 Mersenne Twister）
	static std::mt19937_64 generator(std::random_device{}());

	// 检查范围合法性
	if (min > max)
	{
		throw std::invalid_argument("最小值不能大于最大值！");
	}

	// 定义随机数分布范围
	std::uniform_int_distribution<int64_t> distribution(min, max);

	// 返回随机数
	return distribution(generator);
}

#endif
