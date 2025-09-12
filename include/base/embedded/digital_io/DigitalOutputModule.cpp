#include "DigitalOutputModule.h"
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Slot<base::digital_output_module::DigitalOutputModule>> _provider{};

}

base::Slot<base::digital_output_module::DigitalOutputModule> &
base::digital_output_module::digital_output_module_slot()
{
	return _provider.Instance();
}
