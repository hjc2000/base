#include "UsbFsPcd.h"
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Slot<base::usb_fs_pcd::UsbFsPcd>> _provider{};

}

base::Slot<base::usb_fs_pcd::UsbFsPcd> &base::usb_fs_pcd::usb_fs_pcd_slot()
{
	return _provider.Instance();
}
