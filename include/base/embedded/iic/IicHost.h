#pragma once
#include "base/container/IDictionary.h"
#include "base/define.h"
#include "base/embedded/iic/iic_host_handle.h"
#include "base/task/Mutex.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace iic
	{
		class IicHostOperator;

		///
		/// @brief IIC 主机接口。
		///
		///
		class IicHost
		{
		private:
			DELETE_COPY_AND_MOVE(IicHost)
			friend class IicHostOperator;

			std::shared_ptr<base::iic::iic_host_handle> _handle;
			base::task::Mutex _lock;

		public:
			IicHost(uint32_t id)
			{
				_handle = base::iic::open(id);
			}

			///
			/// @brief 获取 IIC 主机接口的名称。
			///
			/// @return
			///
			std::string Name() const
			{
				return base::iic::name(*_handle);
			}
		};

		///
		/// @brief IIC 主机接口的操作器。
		///
		/// @note IIC 的操作是一个序列，整个操作期间需要保持锁住 IIC 接口，
		/// 不能被打断。操作序列完成后才可以解锁，交给其他线程进行下一个操作序列。
		///
		/// @warning 禁止长时间持有，操作完成后马上析构，否则其他线程永远无法操作同一个
		/// IIC 主机接口。
		///
		class IicHostOperator
		{
		private:
			IicHost &_host;
			base::task::MutexGuard _guard;

		public:
			IicHostOperator(IicHost &host)
				: _host(host),
				  _guard(host._lock)
			{
			}

			///
			/// @brief 初始化 IIC 主机接口。
			///
			/// @param scl_cycle
			/// @param waiting_for_ack_signal_timeout
			///
			void Initialize(base::Nanoseconds const &scl_cycle,
							base::Nanoseconds const &waiting_for_ack_signal_timeout)
			{
				base::iic::initialize(*_host._handle,
									  scl_cycle,
									  waiting_for_ack_signal_timeout);
			}

			///
			/// @brief 发送 IIC 启动信号。
			///
			///
			void SendStartingSignal()
			{
				base::iic::send_starting_signal(*_host._handle);
			}

			///
			/// @brief 发送 IIC 停止信号。
			///
			///
			void SendStoppingSignal()
			{
				base::iic::send_stopping_signal(*_host._handle);
			}

			///
			/// @brief 发送一个字节。
			///
			/// @param byte
			///
			void SendByte(uint8_t byte)
			{
				base::iic::send_byte(*_host._handle, byte);
			}

			///
			/// @brief 读取 1 个字节。
			///
			/// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。
			/// 	@li 传入 true 则发送 nack 信号表示不想继续读了。
			/// 	@li 传入 false 则发送 ack 信号，表示希望继续读取。
			///
			/// @return
			///
			uint8_t ReceiveByte(bool send_nack)
			{
				return base::iic::receive_byte(*_host._handle, send_nack);
			}
		};

		///
		/// @brief IIC 主机的插槽。
		///
		/// @note 初始化阶段打开 IIC 主机，然后插入此插槽。
		///
		/// @return
		///
		base::IDictionary<uint32_t, std::shared_ptr<base::iic::IicHost>> &IicHostIdSlot();

	} // namespace iic
} // namespace base
