#pragma once
#include <cstdint>
#include <limits>
#include <memory>
#include <vector>

namespace base
{
	///
	/// @brief 随机数生成器接口。
	///
	///
	class IRandomGenerator
	{
	public:
		virtual ~IRandomGenerator() = default;

		///
		/// @brief 生成指定范围内的 int64_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return int64_t
		///
		virtual int64_t GenerateInt64Random(int64_t min = std::numeric_limits<int64_t>::min(),
											int64_t max = std::numeric_limits<int64_t>::max()) const = 0;

		///
		/// @brief 生成指定范围内的 uint64_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return uint64_t
		///
		virtual uint64_t GenerateUInt64Random(uint64_t min = std::numeric_limits<uint64_t>::min(),
											  uint64_t max = std::numeric_limits<uint64_t>::max()) const = 0;

		///
		/// @brief 生成指定范围内的 int32_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return int32_t
		///
		int32_t GenerateInt32Random(int32_t min = std::numeric_limits<int32_t>::min(),
									int32_t max = std::numeric_limits<int32_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}

		///
		/// @brief 生成指定范围内的 uint32_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return uint32_t
		///
		uint32_t GenerateUInt32Random(uint32_t min = std::numeric_limits<uint32_t>::min(),
									  uint32_t max = std::numeric_limits<uint32_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}

		///
		/// @brief 生成指定范围内的 int16_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return int16_t
		///
		int16_t GenerateInt16Random(int16_t min = std::numeric_limits<int16_t>::min(),
									int16_t max = std::numeric_limits<int16_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}

		///
		/// @brief 生成指定范围内的 uint16_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return uint16_t
		///
		uint16_t GenerateUInt16Random(uint16_t min = std::numeric_limits<uint16_t>::min(),
									  uint16_t max = std::numeric_limits<uint16_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}

		///
		/// @brief 生成指定范围内的 int8_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return int8_t
		///
		int8_t GenerateInt8Random(int8_t min = std::numeric_limits<int8_t>::min(),
								  int8_t max = std::numeric_limits<int8_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}

		///
		/// @brief 生成指定范围内的 uint8_t 的随机数。
		///
		/// @param min
		/// @param max
		/// @return uint8_t
		///
		uint8_t GenerateUInt8Random(uint8_t min = std::numeric_limits<uint8_t>::min(),
									uint8_t max = std::numeric_limits<uint8_t>::max()) const
		{
			int64_t ret = GenerateInt64Random(static_cast<int64_t>(min), static_cast<int64_t>(max));
			return ret;
		}
	};

	///
	/// @brief 构造一个随机数生成器。
	///
	/// @return std::shared_ptr<base::IRandomGenerator>
	///
	std::shared_ptr<base::IRandomGenerator> CreateRandomGenerator();

	///
	/// @brief 获取一个装着打乱的索引的 std::vector<int64_t>.
	///
	/// @param count 索引的数量。
	/// @return std::vector<int64_t>
	///
	std::vector<int64_t> ShuffleIndex(int64_t count);

} // namespace base
