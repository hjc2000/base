#pragma once
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "serial_handle.h"
#include "serial_parameter.h"
#include <stdexcept>
#include <string>

namespace base
{
	namespace serial
	{
		///
		/// @brief 串口类。
		///
		/// @note 在单片机平台，打开串口前需要自行初始化串口的 GPIO 引脚。
		///
		class Serial :
			public base::Stream
		{
		private:
			std::shared_ptr<base::serial::serial_handle> _handle{};

		public:
			Serial(uint32_t id)
			{
				_handle = base::serial::open(id);
			}

			Serial(std::string const &serial_name)
			{
				_handle = base::serial::open(serial_name);
			}

			~Serial()
			{
				Close();
			}

			/* #region 启动串口 */

			///
			/// @brief 启动串口。
			///
			/// @param direction
			/// @param baud_rate
			/// @param data_bits
			/// @param parity
			/// @param stop_bits
			/// @param hardware_flow_control
			///
			void Start(base::serial::Direction direction,
					   base::serial::BaudRate const &baud_rate,
					   base::serial::DataBits const &data_bits,
					   base::serial::Parity parity,
					   base::serial::StopBits stop_bits,
					   base::serial::HardwareFlowControl hardware_flow_control)
			{
				base::serial::start(*_handle,
									direction,
									baud_rate,
									data_bits,
									parity,
									stop_bits,
									hardware_flow_control);
			}

			///
			/// @brief 启动串口。
			///
			///
			void Start()
			{
				base::serial::start(*_handle);
			}

			///
			/// @brief 启动串口。
			///
			/// @param baud_rate
			///
			void Start(base::serial::BaudRate const &baud_rate)
			{
				base::serial::start(*_handle, baud_rate);
			}

			/* #endregion */

			/* #region 串口属性 */

			///
			/// @brief 获取串口名称。
			///
			/// @return
			///
			std::string Name() const
			{
				return base::serial::name(*_handle);
			}

			///
			/// @brief 数据传输方向。
			///
			/// @return
			///
			base::serial::Direction Direction() const
			{
				return base::serial::direction(*_handle);
			}

			///
			/// @brief 波特率。
			///
			/// @return
			///
			uint32_t BaudRate() const
			{
				return base::serial::baud_rate(*_handle);
			}

			///
			/// @brief 数据位的个数。
			///
			/// @return
			///
			uint8_t DataBits() const
			{
				return base::serial::data_bits(*_handle);
			}

			///
			/// @brief 校验位。
			///
			/// @return
			///
			base::serial::Parity Parity() const
			{
				return base::serial::parity(*_handle);
			}

			///
			/// @brief 停止位个数。
			///
			/// @return
			///
			base::serial::StopBits StopBits() const
			{
				return base::serial::stop_bits(*_handle);
			}

			///
			/// @brief 硬件流控。
			///
			/// @return
			///
			base::serial::HardwareFlowControl HardwareFlowControl() const
			{
				return base::serial::hardware_flow_control(*_handle);
			}

			///
			/// @brief 计算 frame_count 个帧占用多少个波特。
			///
			/// @param frame_count
			///
			/// @return
			///
			uint32_t FramesBaudCount(uint32_t frame_count) const
			{
				return base::serial::frames_baud_count(*_handle, frame_count);
			}

			/* #endregion */

			/* #region 流属性 */

			///
			/// @brief 本流能否读取。
			///
			/// @return true 能读取。
			/// @return false 不能读取。
			///
			virtual bool CanRead() const override
			{
				if (Direction() == base::serial::Direction::RX)
				{
					return true;
				}

				if (Direction() == base::serial::Direction::RX_TX)
				{
					return true;
				}

				return false;
			}

			///
			/// @brief 本流能否写入。
			///
			/// @return true 能写入。
			/// @return false 不能写入。
			///
			virtual bool CanWrite() const override
			{
				if (Direction() == base::serial::Direction::TX)
				{
					return true;
				}

				if (Direction() == base::serial::Direction::RX_TX)
				{
					return true;
				}

				return false;
			}

			///
			/// @brief 本流能否定位。
			///
			/// @return true 能定位。
			/// @return false 不能定位。
			///
			virtual bool CanSeek() const override
			{
				return false;
			}

			///
			/// @brief 流的长度
			///
			/// @return
			///
			virtual int64_t Length() const override
			{
				throw std::runtime_error{CODE_POS_STR + "串口不支持该操作。"};
			}

			///
			/// @brief 设置流的长度。
			///
			/// @param value
			///
			virtual void SetLength(int64_t value) override
			{
				throw std::runtime_error{CODE_POS_STR + "串口不支持该操作。"};
			}

			///
			/// @brief 流当前的位置。
			///
			/// @return
			///
			virtual int64_t Position() const override
			{
				throw std::runtime_error{CODE_POS_STR + "串口不支持该操作。"};
			}

			///
			/// @brief 设置流当前的位置。
			///
			/// @param value
			///
			virtual void SetPosition(int64_t value) override
			{
				throw std::runtime_error{CODE_POS_STR + "串口不支持该操作。"};
			}

			/* #endregion */

			/* #region 读写冲关 */

			using base::Stream::Read;

			///
			/// @brief 将本流的数据读取到 span 中。
			///
			/// @param span
			///
			/// @return
			///
			virtual int64_t Read(base::Span const &span) override
			{
				return base::serial::read(*_handle, span);
			}

			using base::Stream::Write;

			///
			/// @brief 将 span 中的数据写入本流。
			///
			/// @param span
			///
			virtual void Write(base::ReadOnlySpan const &span) override
			{
				base::serial::write(*_handle, span);
			}

			///
			/// @brief 冲洗流。
			///
			/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
			/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
			///
			virtual void Flush() override
			{
				base::serial::flush(*_handle);
			}

			///
			/// @brief 关闭流。
			///
			/// @note 关闭后流无法写入，写入会引发异常。
			///
			/// @note 关闭后流的读取不会引发异常，但是在读完内部残留的数据后，将不会再读到
			/// 任何数据。
			///
			virtual void Close() override
			{
				base::serial::close(*_handle);
			}

			/* #endregion */
		};

	} // namespace serial
} // namespace base
