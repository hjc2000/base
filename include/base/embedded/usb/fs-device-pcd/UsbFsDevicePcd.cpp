#include "UsbFsDevicePcd.h"
#include "base/GlobalObjectProvider.h"

namespace
{
	base::GlobalObjectProvider<base::Slot<base::usb::fs_device_pcd::UsbFsDevicePcd>> _provider{};

}

base::Slot<base::usb::fs_device_pcd::UsbFsDevicePcd> &base::usb::fs_device_pcd::usb_fs_pcd_slot()
{
	return _provider.Instance();
}
