#include "DigitalOutputModule.h"
#include "base/GlobalObjectProvider.h"

namespace
{
	base::GlobalObjectProvider<base::Slot<base::digital_output_module::DigitalOutputModule>> _provider{};

}

base::Slot<base::digital_output_module::DigitalOutputModule> &
base::digital_output_module::digital_output_module_slot()
{
	return _provider.Instance();
}
