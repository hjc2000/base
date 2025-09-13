#include "random.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <random>
#include <stdexcept>

#if HAS_THREAD

namespace
{
	class RandomGenerator :
		public base::IRandomGenerator
	{
	private:
		inline static std::mt19937_64 _generator{std::random_device{}()};

	public:
		virtual int64_t GenerateInt64Random(int64_t min = std::numeric_limits<int64_t>::min(),
											int64_t max = std::numeric_limits<int64_t>::max()) const override
		{
			// 检查范围合法性
			if (min > max)
			{
				throw std::invalid_argument("最小值不能大于最大值！");
			}

			// 定义随机数分布范围
			std::uniform_int_distribution<int64_t> distribution(min, max);

			// 返回随机数
			return distribution(_generator);
		}

		virtual uint64_t GenerateUInt64Random(uint64_t min = std::numeric_limits<uint64_t>::min(),
											  uint64_t max = std::numeric_limits<uint64_t>::max()) const override
		{
			// 检查范围合法性
			if (min > max)
			{
				throw std::invalid_argument("最小值不能大于最大值！");
			}

			// 定义随机数分布范围
			std::uniform_int_distribution<int64_t> distribution(min, max);

			// 返回随机数
			return distribution(_generator);
		}
	};

} // namespace

std::shared_ptr<base::IRandomGenerator> base::CreateRandomGenerator()
{
	return std::shared_ptr<base::IRandomGenerator>{new RandomGenerator{}};
}

std::vector<int64_t> base::ShuffleIndex(int64_t count)
{
	std::vector<int64_t> ret;
	for (int64_t i = 0; i < count; i++)
	{
		ret.push_back(i);
	}

	// 生成随机数引擎
	std::random_device rd;
	std::mt19937 g(rd());

	// 打乱顺序
	std::shuffle(ret.begin(), ret.end(), g);
	return ret;
}

#endif
