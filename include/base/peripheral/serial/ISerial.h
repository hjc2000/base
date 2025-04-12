#pragma once
#include "base/container/IDictionary.h"
#include "base/define.h"
#include "base/stream/Stream.h"
#include "serial_parameter.h"
#include <memory>
#include <string>

namespace base
{
	namespace serial
	{
		///
		/// @brief 串口接口。
		///
		class ISerial :
			public base::Stream
		{
		public:
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
			virtual void Start(base::serial::Direction direction,
							   base::serial::BaudRate const &baud_rate,
							   base::serial::DataBits const &data_bits,
							   base::serial::Parity parity,
							   base::serial::StopBits stop_bits,
							   base::serial::HardwareFlowControl hardware_flow_control) = 0;

			/* #region 串口属性 */

			///
			/// @brief 数据传输方向
			/// @return
			///
			virtual base::serial::Direction Direction() const = 0;

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

			using base::Stream::Read;

			///
			/// @brief 将本流的数据读取到 span 中。
			///
			/// @param span
			/// @return int32_t
			///
			virtual int32_t Read(base::Span const &span) override = 0;

			using base::Stream::Write;

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

			///
			/// @brief 计算 frame_count 个帧占用多少个波特。
			/// @param frame_count
			/// @return
			///
			uint32_t FramesBaudCount(uint32_t frame_count) const;

			/* #region Start */

			///
			/// @brief 使用默认参数打开。
			///
			void Start();

			///
			/// @brief 使用指定的波特率打开。其他参数默认。
			/// @param baud_rate 波特率。
			///
			void Start(base::serial::BaudRate const &baud_rate);

			/* #endregion */
		};

		///
		/// @brief 扫描可用的串口。
		///
		/// @return std::vector<std::string>
		///
		std::vector<std::string> ScanSerials();

		/* #region Open */

		///
		/// @brief 通过串口名称打开串口。
		///
		/// @param name 串口名称。
		///		@note 通用操作系统中使用这种方式。
		///
		/// @return std::shared_ptr<base::serial::ISerial>
		///
		std::shared_ptr<base::serial::ISerial> Open(std::string const &name);

		///
		/// @brief 通过串口 ID 打开串口。
		///
		/// @param serial_id 串口 ID.
		/// 	@note 单片机中使用这种方式。例如想要打开 UART1 就传入 1.
		///
		/// @return std::shared_ptr<base::serial::ISerial>
		///
		std::shared_ptr<base::serial::ISerial> Open(int serial_id);

		/* #endregion */

		///
		/// @brief 主串口。
		///
		/// @note 单片机中通常会有一个主串口，通用计算机中则没有。没有可以不实现本函数，直接让
		/// 本函数抛出异常。
		///
		/// @return
		///
		base::serial::ISerial &MainSerial();

		///
		/// @brief 包含所有可用串口的集合。
		///
		/// @note 这里的串口使用的是单例模式。
		///
		/// @return
		///
		base::IDictionary<std::string, base::AutoPtr<base::serial::ISerial>> const &SerialCollection();

	} // namespace serial
} // namespace base
