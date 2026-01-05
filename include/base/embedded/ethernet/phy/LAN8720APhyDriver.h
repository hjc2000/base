#pragma once
#include "base/embedded/ethernet/parameter.h"
#include "base/embedded/ethernet/phy/IPhyDriver.h"

namespace base
{
	namespace ethernet
	{
		class LAN8720APhyDriver :
			public base::ethernet::IPhyDriver
		{
		private:
			base::ethernet::EthernetController _ethernet_controller;

		public:
			LAN8720APhyDriver(base::ethernet::EthernetController const &controller);

			virtual base::ethernet::EthernetController &EthernetController() override;

			/// @brief 获取此网口的双工模式。
			/// @return
			virtual base::ethernet::DuplexMode DuplexMode() override;

			/// @brief 获取此网口的速度。
			/// @return
			virtual base::unit::Mbps Speed() override;
		};

	} // namespace ethernet
} // namespace base
