#include "UsbFsPcd.h"
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Slot<base::usb::fs_device_pcd::UsbFsPcd>> _provider{};

}

base::Slot<base::usb::fs_device_pcd::UsbFsPcd> &base::usb::fs_device_pcd::usb_fs_pcd_slot()
{
	return _provider.Instance();
}
