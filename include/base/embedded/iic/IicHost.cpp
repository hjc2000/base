#include "IicHost.h"
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Slot<base::iic::IicHost>> _provider{};
}

base::Slot<base::iic::IicHost> &base::iic::iic_host_slot()
{
	return _provider.Instance();
}
