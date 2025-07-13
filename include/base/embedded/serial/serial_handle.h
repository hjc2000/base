#pragma once
#include "base/define.h"
#include "base/embedded/serial/SerialPortInfomation.h"
#include "base/stream/Span.h"
#include "serial_parameter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace base
{
	namespace serial
	{
		class serial_handle;

		///
		/// @brief 扫描可用的串口。
		///
		/// @return
		///
		std::vector<std::string> scan_serials();

		///
		/// @brief 扫描可用的串口，获取详细信息。
		///
		/// @return
		///
		std::vector<base::serial::SerialPortInfomation> scan_serials_for_details();

		/* #region open */

		///
		/// @brief 通过串口名称打开串口。
		///
		/// @param name 串口名称。
		///		@note 通用操作系统中使用这种方式。
		///
		/// @return
		///
		std::shared_ptr<base::serial::serial_handle> open(std::string const &name);

		///
		/// @brief 通过串口 ID 打开串口。
		///
		/// @param id 串口 ID.
		/// 	@note 单片机中使用这种方式。例如想要打开 UART1 就传入 1.
		///
		/// @return
		///
		std::shared_ptr<base::serial::serial_handle> open(uint32_t id);

		/* #endregion */

		/* #region 启动串口 */

		///
		/// @brief 启动串口。
		///
		/// @param h
		/// @param direction
		/// @param baud_rate
		/// @param data_bits
		/// @param parity
		/// @param stop_bits
		/// @param hardware_flow_control
		///
		void start(base::serial::serial_handle &h,
				   base::serial::Direction direction,
				   base::serial::BaudRate const &baud_rate,
				   base::serial::DataBits const &data_bits,
				   base::serial::Parity parity,
				   base::serial::StopBits stop_bits,
				   base::serial::HardwareFlowControl hardware_flow_control);

		///
		/// @brief 启动串口。
		///
		/// @param h
		///
		IMPLEMENTED
		void start(base::serial::serial_handle &h);

		///
		/// @brief 启动串口。
		///
		/// @param h
		/// @param baud_rate
		///
		IMPLEMENTED
		void start(base::serial::serial_handle &h,
				   base::serial::BaudRate const &baud_rate);

		/* #endregion */

		/* #region 串口属性 */

		///
		/// @brief 获取串口名称。
		///
		/// @param h
		/// @return
		///
		std::string name(base::serial::serial_handle &h);

		///
		/// @brief 数据传输方向。
		///
		/// @param h
		/// @return
		///
		base::serial::Direction direction(base::serial::serial_handle &h);

		///
		/// @brief 波特率。
		///
		/// @param h
		/// @return
		///
		uint32_t baud_rate(base::serial::serial_handle &h);

		///
		/// @brief 数据位的个数。
		///
		/// @param h
		/// @return
		///
		uint8_t data_bits(base::serial::serial_handle &h);

		///
		/// @brief 校验位。
		///
		/// @param h
		/// @return
		///
		base::serial::Parity parity(base::serial::serial_handle &h);

		///
		/// @brief 停止位个数。
		///
		/// @param h
		/// @return
		///
		base::serial::StopBits stop_bits(base::serial::serial_handle &h);

		///
		/// @brief 硬件流控。
		///
		/// @param h
		/// @return
		///
		base::serial::HardwareFlowControl hardware_flow_control(base::serial::serial_handle &h);

		///
		/// @brief 计算 frame_count 个帧占用多少个波特。
		///
		/// @param h
		/// @param frame_count
		/// @return
		///
		IMPLEMENTED
		uint32_t frames_baud_count(base::serial::serial_handle &h, uint32_t frame_count);

		/* #endregion */

		///
		/// @brief 从串口读取数据
		///
		/// @param h
		/// @param span
		///
		/// @return 成功读取的字节数。永远不应该返回 0. 应该将本函数实现为等同 Stream
		/// 的 Read 方法。
		///
		int32_t read(base::serial::serial_handle &h, base::Span const &span);

		///
		/// @brief 向串口写入数据。
		///
		/// @param h
		/// @param span
		///
		void write(base::serial::serial_handle &h, base::ReadOnlySpan const &span);

		///
		/// @brief 冲洗串口。
		///
		/// @param h
		///
		void flush(base::serial::serial_handle &h);

	} // namespace serial
} // namespace base
