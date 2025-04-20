#pragma once
#include "base/peripheral/ethernet/EthernetController.h"
#include "base/peripheral/ethernet/parameter.h"
#include "base/peripheral/ethernet/phy/IPhyDriver.h"

namespace base
{
	namespace ethernet
	{
		class YT8512CPhyDriver :
			public base::ethernet::IPhyDriver
		{
		private:
			base::ethernet::EthernetController _ethernet_controller;

		public:
			YT8512CPhyDriver(base::ethernet::EthernetController const &controller);

			virtual base::ethernet::EthernetController &EthernetController() override;

			/// @brief 获取此网口的双工模式。
			/// @return
			virtual base::ethernet::DuplexMode DuplexMode() override;

			/// @brief 获取此网口的速度。
			/// @return
			virtual base::Mbps Speed() override;
		};

	} // namespace ethernet
} // namespace base
