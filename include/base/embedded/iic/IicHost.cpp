#include "IicHost.h" // IWYU pragma: keep
#include "base/container/Dictionary.h"
#include <cstdint>

namespace
{
	base::Dictionary<uint32_t, std::shared_ptr<base::iic::IicHost>> _iic_host_id_slot{};
}

base::IDictionary<uint32_t, std::shared_ptr<base::iic::IicHost>> &base::iic::IicHostIdSlot()
{
	return _iic_host_id_slot;
}
