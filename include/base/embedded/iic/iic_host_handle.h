#pragma once
#include "base/unit/Nanoseconds.h"
#include <cstdint>
#include <memory>
#include <string>

namespace base
{
	namespace iic
	{
		class iic_host_handle;

		std::shared_ptr<base::iic::iic_host_handle> open(uint32_t id);

		///
		/// @brief 获取 IIC 主机接口的名称。
		///
		/// @param h
		/// @return
		///
		std::string name(base::iic::iic_host_handle &h);

		/* #region 锁 */

		///
		/// @brief 锁住 IIC 接口。
		///
		/// @note IIC 的操作是一个序列，整个操作期间需要保持锁住 IIC 接口，
		/// 不能被打断。操作序列完成后才可以解锁，交给其他线程进行下一个操作序列。
		///
		/// @param h
		///
		void lock(base::iic::iic_host_handle &h);

		///
		/// @brief 解锁 IIC 接口。
		///
		/// @param h
		///
		void unlock(base::iic::iic_host_handle &h);

		class iic_host_handle_lock_guard
		{
		private:
			base::iic::iic_host_handle &_handle;

		public:
			iic_host_handle_lock_guard(base::iic::iic_host_handle &handle)
				: _handle(handle)
			{
				base::iic::lock(_handle);
			}

			~iic_host_handle_lock_guard()
			{
				base::iic::unlock(_handle);
			}
		};

		/* #endregion */

		///
		/// @brief 初始化 IIC 主机接口。
		///
		/// @param h
		/// @param scl_cycle
		/// @param waiting_for_ack_signal_timeout
		///
		void initialize(base::iic::iic_host_handle &h,
						base::Nanoseconds const &scl_cycle,
						base::Nanoseconds const &waiting_for_ack_signal_timeout);

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

		///
		/// @brief SCL 信号的周期。
		///
		/// @param h
		/// @return
		///
		base::Nanoseconds scl_cycle(base::iic::iic_host_handle &h);

	} // namespace iic
} // namespace base
