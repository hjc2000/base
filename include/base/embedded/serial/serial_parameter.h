#pragma once
#include <cstdint>

namespace base
{
	namespace serial
	{
		///
		/// @brief 校验方式
		///
		enum class Parity
		{
			///
			/// @brief 不校验。
			///
			None,

			///
			/// @brief 偶校验。
			///
			Even,

			///
			/// @brief 奇校验。
			///
			Odd,
		};

		///
		/// @brief 停止位位数。
		///
		enum class StopBits
		{
			///
			/// @brief 0.5
			///
			ZeroPointFive,

			///
			/// @brief 1
			///
			One,

			///
			/// @brief 1.5
			///
			OnePointFive,

			///
			/// @brief 2
			///
			Two,
		};

		///
		/// @brief 硬件流控。
		///
		enum class HardwareFlowControl
		{
			None,
			RTS,
			CTS,
			RTS_CTS,
		};

		///
		/// @brief 串口数据传输方向。
		///
		enum class Direction
		{
			RX,
			TX,
			RX_TX,
		};

		///
		/// @brief 波特率。
		///
		class BaudRate
		{
		private:
			uint32_t _value = 0;

		public:
			explicit BaudRate(uint32_t value)
				: _value(value)
			{
			}

			uint32_t Value() const
			{
				return _value;
			}
		};

		///
		/// @brief 数据位位数。
		///
		class DataBits
		{
		private:
			uint8_t _value = 0;

		public:
			explicit DataBits(uint8_t value)
				: _value(value)
			{
			}

			uint8_t Value() const
			{
				return _value;
			}
		};

	} // namespace serial
} // namespace base
