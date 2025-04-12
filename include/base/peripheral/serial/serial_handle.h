#pragma once
#include "base/stream/Span.h"
#include "serial_parameter.h"
#include <memory>
#include <string>
#include <vector>

namespace base
{
	namespace serial
	{
		class serial_handle;
		using sp_serial_handle = std::shared_ptr<serial_handle>;

		///
		/// @brief 扫描可用的串口。
		///
		/// @return std::vector<std::string>
		///
		std::vector<std::string> scan_serials();

		/* #region open */

		///
		/// @brief 通过串口名称打开串口。
		///
		/// @param name 串口名称。
		///		@note 通用操作系统中使用这种方式。
		///
		/// @return base::serial::sp_serial_handle
		///
		base::serial::sp_serial_handle open(std::string const &name);

		///
		/// @brief 通过串口 ID 打开串口。
		///
		/// @param serial_id 串口 ID.
		/// 	@note 单片机中使用这种方式。例如想要打开 UART1 就传入 1.
		///
		/// @return base::serial::sp_serial_handle
		///
		base::serial::sp_serial_handle open(int serial_id);

		/* #endregion */

		/* #region 串口属性 */

		///
		/// @brief 获取串口名称。
		///
		/// @param h
		/// @return std::string
		///
		std::string name(base::serial::sp_serial_handle const &h);

		///
		/// @brief 数据传输方向
		/// @return
		///
		base::serial::Direction direction();

		///
		/// @brief 波特率。
		/// @return
		///
		uint32_t baud_rate();

		///
		/// @brief 数据位的个数。
		/// @return
		///
		uint8_t data_bits();

		///
		/// @brief 校验位。
		/// @return
		///
		base::serial::Parity parity();

		///
		/// @brief 停止位个数。
		/// @return
		///
		base::serial::StopBits stop_bits();

		///
		/// @brief 硬件流控。
		///
		/// @return
		///
		base::serial::HardwareFlowControl hardware_flow_control();

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
		void start(base::serial::sp_serial_handle const &h,
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
		inline void start(base::serial::sp_serial_handle const &h)
		{
			start(h,
				  base::serial::Direction::RX_TX,
				  base::serial::BaudRate{115200},
				  base::serial::DataBits{8},
				  base::serial::Parity::None,
				  base::serial::StopBits::One,
				  base::serial::HardwareFlowControl::None);
		}

		///
		/// @brief 启动串口。
		///
		/// @param h
		/// @param baud_rate
		///
		inline void start(base::serial::sp_serial_handle const &h,
						  base::serial::BaudRate const &baud_rate)
		{
			start(h,
				  base::serial::Direction::RX_TX,
				  baud_rate,
				  base::serial::DataBits{8},
				  base::serial::Parity::None,
				  base::serial::StopBits::One,
				  base::serial::HardwareFlowControl::None);
		}

		/* #endregion */

		int32_t read(base::serial::sp_serial_handle const &h, base::Span const &span);

		void write(base::serial::sp_serial_handle const &h, base::ReadOnlySpan const &span);

		void flush(base::serial::sp_serial_handle const &h);

	} // namespace serial
} // namespace base
