#pragma once
#include "MemoryType.h"
#include <cstddef>
#include <cstdint>

namespace base::cortex::mpu
{
	void configure(uint32_t region_number,
				   size_t base_address,
				   size_t size,
				   base::cortex::MemoryType memory_type);

}
