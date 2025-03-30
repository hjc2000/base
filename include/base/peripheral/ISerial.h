#pragma once
#include "base/container/IDictionary.h"
#include "base/stream/Stream.h"
#include <string>

namespace base
{
	/// @brief 参数、枚举
	namespace serial
	{
		/* #region 串口属性 */

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
			Tow,
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

		/* #endregion */

		///
		/// @brief 串口接口。
		///
		class ISerial :
			public base::Stream
		{
		public:
			virtual ~ISerial() = default;

			///
			/// @brief 串口名称。
			///
			/// @return std::string
			///
			virtual std::string Name() = 0;

			/* #region Open */

			///
			/// @brief 打开串口。
			///
			/// @param direction 串口数据方向。可以选择只发、只收、收发。
			/// @param baud_rate 波特率。
			/// @param data_bits 数据位位数。
			/// @param parity 奇偶校验。
			/// @param stop_bits 停止位位数。
			/// @param hardware_flow_control 硬件流控。
			///
			virtual void Open(base::serial::Direction direction,
							  base::serial::BaudRate const &baud_rate,
							  base::serial::DataBits const &data_bits,
							  base::serial::Parity parity,
							  base::serial::StopBits stop_bits,
							  base::serial::HardwareFlowControl hardware_flow_control) = 0;

			///
			/// @brief 使用默认参数打开。
			///
			void Open();

			///
			/// @brief 使用指定的波特率打开。其他参数默认。
			/// @param baud_rate 波特率。
			///
			void Open(base::serial::BaudRate const &baud_rate);

			/* #endregion */

			///
			/// @brief 串口已经打开。
			///
			/// @return true 已经打开。
			/// @return false 还没打开。
			///
			virtual bool IsOpen() const = 0;

			/* #region 串口属性 */

			///
			/// @brief 数据传输方向
			/// @return
			///
			virtual base::serial::Direction Direction() = 0;

			///
			/// @brief 波特率。
			/// @return
			///
			virtual uint32_t BaudRate() const = 0;

			///
			/// @brief 数据位的个数。
			/// @return
			///
			virtual uint8_t DataBits() const = 0;

			///
			/// @brief 校验位。
			/// @return
			///
			virtual base::serial::Parity Parity() const = 0;

			///
			/// @brief 停止位个数。
			/// @return
			///
			virtual base::serial::StopBits StopBits() const = 0;

			///
			/// @brief 硬件流控。
			/// @return
			///
			virtual base::serial::HardwareFlowControl HardwareFlowControl() const = 0;

			///
			/// @brief 计算 frame_count 个帧占用多少个波特。
			/// @param frame_count
			/// @return
			///
			uint32_t FramesBaudCount(uint32_t frame_count) const;

			/* #endregion */

			/* #region 流属性 */

			///
			/// @brief 本流能否读取。
			///
			/// @return true 能读取。
			/// @return false 不能读取。
			///
			virtual bool CanRead() const override = 0;

			///
			/// @brief 本流能否写入。
			///
			/// @return true 能写入。
			/// @return false 不能写入。
			///
			virtual bool CanWrite() const override = 0;

			///
			/// @brief 本流能否定位。
			///
			/// @return true 能定位。
			/// @return false 不能定位。
			///
			virtual bool CanSeek() const override = 0;

			///
			/// @brief 流的长度
			///
			/// @return int64_t
			///
			virtual int64_t Length() const override = 0;

			///
			/// @brief 设置流的长度。
			///
			/// @param value
			///
			virtual void SetLength(int64_t value) override = 0;

			///
			/// @brief 流当前的位置。
			///
			/// @return int64_t
			///
			virtual int64_t Position() const override = 0;

			///
			/// @brief 设置流当前的位置。
			///
			/// @param value
			///
			virtual void SetPosition(int64_t value) override = 0;

			/* #endregion */

			/* #region 读写冲关 */

			///
			/// @brief 将本流的数据读取到 span 中。
			///
			/// @param span
			/// @return int32_t
			///
			virtual int32_t Read(base::Span const &span) override = 0;

			///
			/// @brief 将 span 中的数据写入本流。
			///
			/// @param span
			///
			virtual void Write(base::ReadOnlySpan const &span) override = 0;

			///
			/// @brief 冲洗流。
			///
			/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
			/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
			///
			virtual void Flush() override = 0;

			///
			/// @brief 关闭流。
			///
			/// @note 关闭后对流的操作将会引发异常。
			///
			/// @note 因为本接口是串口接口，所以关闭流也等于关闭串口。
			///
			virtual void Close() override = 0;

			/* #endregion */
		};

		///
		/// @brief 包含所有可用串口的集合。
		///
		/// @note 这里的串口使用的是单例模式。
		///
		/// @return
		///
		base::IDictionary<std::string, base::serial::ISerial *> const &SerialCollection();

	} // namespace serial
} // namespace base
