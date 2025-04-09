#pragma once
#include "ISerial.h"
#include <cstdint>

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

		class DmaContext;

		///
		/// @brief DMA 接口。
		///
		///
		class IDma
		{
		public:
			virtual base::dma::DmaContext &Context() = 0;
		};

		/* #region 全局的 DMA 打开函数 */

		PLATFORM_IMPLEMENTATION_REQUIRED
		void OpenForSerialReceiving(base::dma::IDma *dma, base::serial::ISerial *serial);

		PLATFORM_IMPLEMENTATION_REQUIRED
		void OpenForSerialSending(base::dma::IDma *dma, base::serial::ISerial *serial);

		/* #endregion */

		///
		/// @brief 获取 DMA 本次启动后剩余的未传输的字节数。
		///
		/// @note 将本次启动 DMA 所设置的目标传输字节数减去本属性，即可得到传输了多少个字节。
		///
		/// @param dma
		/// @return int32_t
		///
		PLATFORM_IMPLEMENTATION_REQUIRED
		int32_t RemainingUntransmittedBytes(base::dma::IDma *dma);

	} // namespace dma
} // namespace base
