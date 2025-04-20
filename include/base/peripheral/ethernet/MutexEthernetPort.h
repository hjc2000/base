#pragma once
#include "base/delegate/IEvent.h"
#include "base/task/IMutex.h"
#include "IEthernetPort.h"

namespace base
{
	namespace ethernet
	{
		class MutexEthernetPort :
			public base::ethernet::IEthernetPort
		{
		private:
			///
			/// @brief 接收用的锁。
			///
			/// @note 以太网是双工的，接收和发送不能使用同一个锁。
			///
			std::shared_ptr<base::IMutex> _receiving_lock = base::CreateIMutex();

			///
			/// @brief 发送用的锁。
			///
			/// @note 以太网是双工的，接收和发送不能使用同一个锁。
			///
			std::shared_ptr<base::IMutex> _sending_lock = base::CreateIMutex();

			base::ethernet::IEthernetPort *_port = nullptr;

		public:
			MutexEthernetPort(base::ethernet::IEthernetPort *port)
			{
				_port = port;
			}

			///
			/// @brief 打开以太网端口。
			///
			/// @param mac MAC 地址。
			///
			virtual void Open(base::Mac const &mac) override
			{
				_port->Open(mac);
			}

			///
			/// @brief 发送。
			///
			/// @param spans
			///
			virtual void Send(std::vector<base::ReadOnlySpan> const &spans) override
			{
				base::LockGuard l{*_sending_lock};
				_port->Send(spans);
			}

			///
			/// @brief 发送。
			///
			/// @param span
			///
			virtual void Send(base::ReadOnlySpan const &span) override
			{
				base::LockGuard l{*_sending_lock};
				_port->Send(span);
			}

			///
			/// @brief 收到以太网帧会触发此事件。
			///
			/// @note 事件回调中会传入一个装有完整的以太网帧的 base::ReadOnlySpan.
			///
			/// @return
			///
			virtual base::IEvent<base::ReadOnlySpan> &ReceivingEhternetFrameEvent() override
			{
				return _port->ReceivingEhternetFrameEvent();
			}

			///
			/// @brief 连接事件。
			///
			/// @note 链路层连接建立后会触发事件。
			///
			/// @return
			///
			virtual base::IEvent<> &ConnectedEvent() override
			{
				return _port->ConnectedEvent();
			}

			///
			/// @brief 断开连接事件。
			///
			/// @note 链路层连接断开后会触发事件。
			///
			/// @return
			///
			virtual base::IEvent<> &DisconnectedEvent() override
			{
				return _port->DisconnectedEvent();
			}
		};
	} // namespace ethernet
} // namespace base
