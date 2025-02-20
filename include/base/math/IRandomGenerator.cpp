#include "IRandomGenerator.h"
#include <base/define.h>
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
		inline static_field std::mt19937_64 _generator{std::random_device{}()};

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

std::shared_ptr<base::IRandomGenerator> base::di::CreateRandomGenerator()
{
	return std::shared_ptr<base::IRandomGenerator>{new RandomGenerator{}};
}

#endif
