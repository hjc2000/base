#pragma once

namespace base
{
	namespace dma
	{
		///
		/// @brief DMA 优先级
		///
		///
		enum class Priority
		{
			Low,
			Medium,
			High,
			VeryHigh,
		};

		///
		/// @brief DMA 在读写外设地址空间时，是否自动递增地址。即每读取 1 个字节，
		/// 就将地址递增 1.
		///
		enum class PeripheralIncrement
		{
			Increase,
			DoNotIncrease,
		};

		///
		/// @brief DMA 在读写内存地址空间时是否自动递增地址。即每读取 1 个字节，
		/// 就将地址递增 1.
		///
		enum class MemoryIncrement
		{
			Increase,
			DoNotIncrease,
		};

		///
		/// @brief DMA 读写外设时采用的数据对齐字节数。例如 1 字节对齐或 4 字节对齐。
		///
		///
		class PeripheralDataAlignment
		{
		private:
			int _value = 4;

		public:
			constexpr explicit PeripheralDataAlignment(int value)
			{
				_value = value;
			}

			constexpr int Value() const
			{
				return _value;
			}
		};

		///
		/// @brief DMA 读写内存时采用的数据对齐字节数。例如 1 字节对齐或 4 字节对齐。
		///
		///
		class MemoryDataAlignment
		{
		private:
			int _value = 4;

		public:
			constexpr explicit MemoryDataAlignment(int value)
			{
				_value = value;
			}

			constexpr int Value() const
			{
				return _value;
			}
		};

	} // namespace dma
} // namespace base
