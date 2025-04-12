#pragma once
#include "serial_handle.h"
#include <string>

namespace base
{
	namespace serial
	{
		class Serial
		{
		private:
			base::serial::sp_serial_handle _handle{};

		public:
			Serial(int serial_id)
			{
				_handle = base::serial::open(serial_id);
			}

			Serial(std::string const &serial_name)
			{
				_handle = base::serial::open(serial_name);
			}

			/* #region 串口属性 */

			///
			/// @brief 获取串口名称。
			///
			/// @return std::string
			///
			std::string Name() const
			{
				return base::serial::name(_handle);
			}

			///
			/// @brief 数据传输方向。
			///
			/// @return base::serial::Direction
			///
			base::serial::Direction Direction() const
			{
				return base::serial::direction(_handle);
			}

			///
			/// @brief 波特率。
			///
			/// @return uint32_t
			///
			uint32_t BaudRate() const
			{
				return base::serial::baud_rate(_handle);
			}

			///
			/// @brief 数据位的个数。
			///
			/// @return uint8_t
			///
			uint8_t DataBits() const
			{
				return base::serial::data_bits(_handle);
			}

			///
			/// @brief 校验位。
			///
			/// @return base::serial::Parity
			///
			base::serial::Parity Parity() const
			{
				return base::serial::parity(_handle);
			}

			///
			/// @brief 停止位个数。
			///
			/// @return base::serial::StopBits
			///
			base::serial::StopBits StopBits() const
			{
				return base::serial::stop_bits(_handle);
			}

			///
			/// @brief 硬件流控。
			///
			/// @return base::serial::HardwareFlowControl
			///
			base::serial::HardwareFlowControl HardwareFlowControl() const
			{
				return base::serial::hardware_flow_control(_handle);
			}

			///
			/// @brief 计算 frame_count 个帧占用多少个波特。
			///
			/// @param frame_count
			/// @return uint32_t
			///
			uint32_t FramesBaudCount(uint32_t frame_count) const
			{
				return base::serial::frames_baud_count(_handle, frame_count);
			}

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
		};
	} // namespace serial
} // namespace base
