#pragma once
#include "base/embedded/Slot.h"

namespace base
{
	namespace usb_fs_pcd
	{
		class UsbFsPcd
		{
		public:
		};

		base::Slot<base::usb_fs_pcd::UsbFsPcd> &usb_fs_pcd_slot();

	} // namespace usb_fs_pcd
} // namespace base
