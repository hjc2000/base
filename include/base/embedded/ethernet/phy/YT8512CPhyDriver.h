#pragma once
#include "base/embedded/ethernet/EthernetController.h"
#include "base/embedded/ethernet/parameter.h"
#include "base/embedded/ethernet/phy/IPhyDriver.h"
#include "base/string/define.h"
#include "base/unit/Mbps.h"

namespace base::ethernet
{
	class YT8512CPhyDriver :
		public base::ethernet::IPhyDriver
	{
	private:
		base::ethernet::EthernetController _ethernet_controller;

	public:
		YT8512CPhyDriver(base::ethernet::EthernetController const &controller)
			: _ethernet_controller(controller)
		{
		}

		virtual base::ethernet::EthernetController &EthernetController() override
		{
			return _ethernet_controller;
		}

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual base::ethernet::DuplexMode DuplexMode() override
		{
			uint32_t register_value = ReadRegister(0x11);
			uint32_t const mask = 0b1 << 13;
			uint32_t duplex_register = (register_value & mask) >> 13;

			if (duplex_register)
			{
				return base::ethernet::DuplexMode::FullDuplex;
			}

			return base::ethernet::DuplexMode::HalfDuplex;
		}

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::unit::Mbps Speed() override
		{
			uint32_t register_value = ReadRegister(0x11);
			uint32_t const mask = 0b11 << 14;
			uint32_t duplex_register = (register_value & mask) >> 14;

			if (duplex_register == 0b00)
			{
				return base::unit::Mbps{10};
			}
			else if (duplex_register == 0b01)
			{
				return base::unit::Mbps{100};
			}
			else if (duplex_register == 0b01)
			{
				return base::unit::Mbps{1000};
			}
			else
			{
				throw std::runtime_error{CODE_POS_STR + "读取连接速率寄存器时读取到保留值。"};
			}
		}
	};

} // namespace base::ethernet
