#include "DigitalInputModule.h"
#include "base/GlobalObjectProvider.h"

namespace
{
	base::GlobalObjectProvider<base::Slot<base::digital_input_module::DigitalInputModule>> _provider{};
}

base::Slot<base::digital_input_module::DigitalInputModule> &
base::digital_input_module::digital_input_module_slot()
{
	return _provider.Instance();
}
