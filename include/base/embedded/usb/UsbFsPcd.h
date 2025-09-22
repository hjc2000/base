#pragma once
#include "base/embedded/Slot.h"
#include "usb_fs_pcd_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace usb_fs_pcd
	{
		class UsbFsPcd
		{
		private:
			std::shared_ptr<base::usb_fs_pcd::usb_fs_pcd_handle> _handle;

		public:
			UsbFsPcd(uint32_t id)
			{
				_handle = base::usb_fs_pcd::open(id);
			}

			void InitializeAsDevice(std::string const &clock_source_name,
									uint32_t divider,
									base::usb::PhyType phy_type)
			{
				base::usb_fs_pcd::initialize_as_device(*_handle,
													   clock_source_name,
													   divider,
													   phy_type);
			}
		};

		base::Slot<base::usb_fs_pcd::UsbFsPcd> &usb_fs_pcd_slot();

	} // namespace usb_fs_pcd
} // namespace base
