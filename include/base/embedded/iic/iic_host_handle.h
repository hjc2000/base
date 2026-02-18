#pragma once
#include "base/embedded/iic/ISoftwareIicHostPinDriver.h"
#include "base/unit/Nanosecond.h"
#include <cstdint>
#include <memory>
#include <string>

namespace base
{
	namespace iic
	{
		class iic_host_handle;

		std::shared_ptr<base::iic::iic_host_handle> open(uint32_t id);

		std::shared_ptr<base::iic::iic_host_handle> open(std::shared_ptr<base::iic::ISoftwareIicHostPinDriver> const &pin_driver);

		///
		/// @brief 获取 IIC 主机接口的名称。
		///
		/// @param h
		/// @return
		///
		std::string name(base::iic::iic_host_handle &h);

		///
		/// @brief 初始化 IIC 主机接口。
		///
		/// @param h
		/// @param scl_cycle
		/// @param waiting_for_ack_signal_timeout
		///
		void initialize(base::iic::iic_host_handle &h,
						base::unit::Nanosecond const &scl_cycle,
						base::unit::Nanosecond const &waiting_for_ack_signal_timeout);

		///
		/// @brief 发送 IIC 启动信号。
		///
		/// @param h
		///
		void send_starting_signal(base::iic::iic_host_handle &h);

		///
		/// @brief 发送 IIC 停止信号。
		///
		/// @param h
		///
		void send_stopping_signal(base::iic::iic_host_handle &h);

		///
		/// @brief 发送一个字节。
		///
		/// @param h
		/// @param byte
		///
		void send_byte(base::iic::iic_host_handle &h, uint8_t byte);

		///
		/// @brief 读取 1 个字节。
		///
		/// @param h
		///
		/// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。
		/// 	@li 传入 true 则发送 nack 信号表示不想继续读了。
		/// 	@li 传入 false 则发送 ack 信号，表示希望继续读取。
		///
		/// @return
		///
		uint8_t receive_byte(base::iic::iic_host_handle &h, bool send_nack);

	} // namespace iic
} // namespace base
