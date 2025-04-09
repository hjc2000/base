#pragma once
#include "ISerial.h"

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

		///
		/// @brief DMA 接口。
		///
		///
		class IDma
		{
		public:
		};

		/* #region 全局的 DMA Open 函数 */

		///
		/// @brief 打开 DMA.
		///
		/// @param dma 要打开的 DMA 对象。
		/// @param parent DMA 要连接到的父设备。
		/// @param peripheral_increment
		/// @param memory_increment
		/// @param peripheral_data_alignment
		/// @param memory_data_alignment
		/// @param priority
		///
		void Open(base::dma::IDma *dma,
				  base::serial::ISerial *parent,
				  base::dma::PeripheralIncrement peripheral_increment,
				  base::dma::MemoryIncrement memory_increment,
				  base::dma::PeripheralDataAlignment const &peripheral_data_alignment,
				  base::dma::MemoryDataAlignment const &memory_data_alignment,
				  base::dma::Priority priority);

		/* #endregion */

	} // namespace dma
} // namespace base
