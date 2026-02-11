#pragma once
#include "base/embedded/ethernet/parameter.h"
#include "base/embedded/ethernet/phy/IPhyDriver.h"
#include "base/unit/Mbps.h"

namespace base::ethernet
{
	class LAN8720APhyDriver :
		public base::ethernet::IPhyDriver
	{
	private:
		base::ethernet::EthernetController _ethernet_controller;

	public:
		LAN8720APhyDriver(base::ethernet::EthernetController const &controller)
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
			uint32_t register_value = ReadRegister(0x1F);
			uint32_t const mask = 0b10000;
			if (register_value & mask)
			{
				return base::ethernet::DuplexMode::FullDuplex;
			}

			return base::ethernet::DuplexMode::HalfDuplex;
		}

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::unit::Mbps Speed() override
		{
			uint32_t register_value = ReadRegister(0x1F);
			uint32_t const mask = 0b01000;
			if (register_value & mask)
			{
				return base::unit::Mbps{100};
			}

			return base::unit::Mbps{10};
		}
	};

} // namespace base::ethernet
