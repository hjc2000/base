#pragma once
#include "base/task/delay.h"
#include "base/unit/Nanosecond.h"
#include "SoftwareIicHostPinDriver.h"
#include <chrono>
#include <memory>

namespace base
{
	namespace iic
	{
		class SoftwareIicHost
		{
		private:
			std::shared_ptr<base::iic::ISoftwareIicHostPinDriver> _pin_driver;
			base::unit::Nanosecond _scl_cycle;
			base::unit::Nanosecond _waiting_for_ack_signal_timeout;

			/* #region 收发 IIC 控制信号 */

			///
			/// @brief 发送应答信号。
			///
			void SendAcknowledgment()
			{
				_pin_driver->WriteSCL(false);
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Output);
				_pin_driver->WriteSDA(false);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(false);
			}

			///
			/// @brief 发送非应答信号。
			///
			void SendNotAcknowledgment()
			{
				_pin_driver->WriteSCL(false);
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Output);
				_pin_driver->WriteSDA(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(false);
			}

			///
			/// @brief 等待应答信号。
			///
			/// @return 成功等到应答信号返回 true，没有等到返回 false.
			///
			bool WaitForAcknowledgment()
			{
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Input);
				_pin_driver->WriteSDA(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));

				base::unit::Nanosecond waiting_time{};
				while (_pin_driver->ReadSDA())
				{
					if (waiting_time > _waiting_for_ack_signal_timeout)
					{
						SendStoppingSignal();
						return false;
					}

					base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
					waiting_time += _scl_cycle / 2;
				}

				_pin_driver->WriteSCL(false);
				return true;
			}

			/* #endregion */

			/* #region 收发一位数据 */

			///
			/// @brief 发送一位数据。
			///
			/// @param value
			///
			void SendBit(bool value)
			{
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Output);
				_pin_driver->WriteSCL(false);
				_pin_driver->WriteSDA(value);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(false);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
			}

			///
			/// @brief 接收一个位。
			///
			/// @return
			///
			bool ReceiveBit()
			{
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Input);
				_pin_driver->WriteSCL(false);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				_pin_driver->WriteSCL(true);
				bool bit = _pin_driver->ReadSDA();
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle / 2));
				return bit;
			}

			/* #endregion */

		public:
			SoftwareIicHost(std::shared_ptr<base::iic::ISoftwareIicHostPinDriver> const &pin_driver)
			{
				_pin_driver = pin_driver;
			}

			void Initialize(base::unit::Nanosecond const &scl_cycle,
							base::unit::Nanosecond const &waiting_for_ack_signal_timeout)
			{
				_scl_cycle = scl_cycle;
				_waiting_for_ack_signal_timeout = waiting_for_ack_signal_timeout;
			}

			///
			/// @brief 发送 IIC 启动信号。
			///
			void SendStartingSignal()
			{
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Output);
				_pin_driver->WriteSDA(true);
				_pin_driver->WriteSCL(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle));
				_pin_driver->WriteSDA(false);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle));
				_pin_driver->WriteSCL(false);
			}

			///
			/// @brief 发送 IIC 停止信号。
			///
			void SendStoppingSignal()
			{
				_pin_driver->ChangeSDADirection(base::gpio::Direction::Output);
				_pin_driver->WriteSCL(false);
				_pin_driver->WriteSDA(false);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle));
				_pin_driver->WriteSCL(true);
				_pin_driver->WriteSDA(true);
				base::task::Delay(static_cast<std::chrono::nanoseconds>(_scl_cycle));
			}

			///
			/// @brief 发送一个字节。
			/// @param value
			///
			void SendByte(uint8_t value)
			{
				for (int i = 0; i < 8; i++)
				{
					// 取出最高位。IIC 是从最高位开始发送。
					bool bit = value & 0x80;
					SendBit(bit);

					// 将次高位变成最高位。
					value <<= 1;
				}

				bool ack = WaitForAcknowledgment();
				if (!ack)
				{
					throw std::runtime_error{"IIC 接口发送数据时未收到从机的应答信号"};
				}
			}

			///
			/// @brief 读取 1 个字节。
			///
			/// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。传入 true 则发送 nack 信号，
			/// 传入 false 则发送 ack 信号，表示希望继续读取。
			///
			/// @return
			///
			uint8_t ReceiveByte(bool send_nack)
			{
				uint8_t data = 0;
				for (int i = 0; i < 8; i++)
				{
					bool bit = ReceiveBit();
					data <<= 1;
					if (bit)
					{
						data |= 0x1;
					}
				}

				if (send_nack)
				{
					SendNotAcknowledgment();
				}
				else
				{
					SendAcknowledgment();
				}

				return data;
			}
		};
	} // namespace iic
} // namespace base
