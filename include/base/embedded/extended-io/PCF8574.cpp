#include "PCF8574.h" // IWYU pragma: keep
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Slot<base::extended_io::PCF8574>> _provider{};
}

base::Slot<base::extended_io::PCF8574> &base::extended_io::pcf8574_slot()
{
	return _provider.Instance();
}
